#!/usr/bin/env python3

import sys
import argparse
import platform
from logging import basicConfig, getLogger
from os import getenv
from pathlib import Path
import sysconfig
import os
import shutil
import hashlib
import json
from datetime import datetime
from subprocess import (PIPE, STDOUT, CalledProcessError,
                        TimeoutExpired, check_call, run)
from tempfile import TemporaryDirectory
from typing import Any, Iterator, List, MutableMapping, Optional, Union

from enum import Enum
import toml

logger = getLogger(__name__)

CASENAME_LEN_LIMIT = 40
STACK_SIZE = 2 ** 28  # 256 MB


def casename(name: Union[str, Path], i: int) -> str:
    """(random, 1) -> random_01"""
    return Path(name).stem + '_' + str(i).zfill(2)


def param_to_str(key: str, value: object):
    if isinstance(value, int):
        return '#define {} (long long){}'.format(key, value)
    elif isinstance(value, float):
        return '#define {} {}'.format(key, value)
    elif isinstance(value, str):
        # NOTE: this fails if value contains some chars like double quotations
        return '#define {} "{}"'.format(key, value)
    else:
        raise RuntimeError('Unsupported type of params: {}'.format(key))


def find_problem_dir(rootdir: Path, problem_name: Path) -> Optional[Path]:
    tomls = list(rootdir.glob('**/{}/info.toml'.format(problem_name)))
    if len(tomls) == 0:
        logger.error('Cannot find problem: {}'.format(problem_name))
        return None
    if len(tomls) >= 2:
        logger.error('Found multiple problem dirs: {}'.format(problem_name))
        return None
    return tomls[0].parent


def compile(src: Path, rootdir: Path, opts: List[str] = []):
    if src.suffix == '.cpp':
        # use clang for msys2 clang environment
        if os.name == 'nt' and sysconfig.get_platform().startswith('mingw') and sysconfig.get_platform().endswith('clang'):
            cxx = getenv('CXX', 'clang++')
        else:
            cxx = getenv('CXX', 'g++')
        cxxflags_default = '-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'
        if platform.system() == 'Darwin':
            cxxflags_default += ' -Wl,-stack_size,{}'.format(hex(STACK_SIZE))
        if platform.system() == 'Windows':
            cxxflags_default += ' -Wl,-stack,{}'.format(hex(STACK_SIZE))
            # avoid using MinGW's "unique" stdio, which doesn't recognize %lld
            cxxflags_default += ' -D__USE_MINGW_ANSI_STDIO'
            # avoid CI issue, ref https://github.com/yosupo06/library-checker-problems/issues/1031
            cxxflags_default += ' -static'
        if platform.uname().system == 'Linux' and 'microsoft' in platform.uname().release.lower():
            # a workaround for the lack of ulimit in Windows Subsystem for Linux
            cxxflags_default += ' -fsplit-stack'
        cxxflags = getenv('CXXFLAGS', cxxflags_default).split()
        cxxflags.extend(['-I', str(rootdir / 'common')])
        args = [cxx] + cxxflags + \
            ['-o', str(src.with_suffix(''))] + opts + [str(src)]
        logger.debug('compile: %s', args)
        check_call(args)
    elif src.suffix == '.in':
        pass
    elif src.suffix == '.py':
        pass
    else:
        logger.error('Unknown type of file {}'.format(src))
        raise RuntimeError('Unknown type of file: {}'.format(src))


def execcmd(src: Path, arg: List[str] = []) -> List[str]:
    """
    main.cpp -> ['main']
    example.in -> ['cat', 'example_00.in']
    """
    if src.suffix == '.cpp':
        cmd = [str(src.with_suffix('' if platform.system()
                                   != 'Windows' else '.exe').resolve())]
        cmd.extend(arg)
        return cmd
    elif src.suffix == '.py':
        return [sys.executable, str(src)]
    elif src.suffix == '.in':
        inpath = src.with_name(casename(src, int(arg[0])) + '.in')
        # see https://www.msys2.org/docs/python/ for using msys2
        if platform.system() == 'Windows' and not (os.name == 'nt' and sysconfig.get_platform().startswith("mingw")):
            # Windows' built-in command
            cmd = ['cmd', '/C', 'type', str(inpath)]
        else:
            cmd = ['cat', str(inpath)]
        return cmd
    else:
        raise RuntimeError('Unknown file: {} {}'.format(src, arg))


def check_call_to_file(command: List[str], outpath: Path, *args, **kwargs):
    logger.debug('check_call_to_file: %s', command)
    with open(outpath, "w") as outfile:
        check_call(command, stdout=outfile, *args, **kwargs)
    if platform.uname().system == 'Windows':
        # handles CRLF stuff on Windows
        with TemporaryDirectory() as tmpdir:
            tmppath = Path(tmpdir).joinpath('file')
            shutil.move(outpath, tmppath)
            with open(tmppath, "r") as tmpfile, open(outpath, "w", newline='\n') as outfile:
                for line in tmpfile:
                    outfile.write(line)


def logging_result(result: str, start: datetime, end: datetime, message: str):
    elapsed_millis = (end - start).seconds*1000 + \
        (end - start).microseconds // 1000
    logger.info('{:>3s} {:6d} msecs : {}'.format(
        result, elapsed_millis, message))


class Problem:
    class Mode(Enum):
        DEFAULT = 1
        DEV = 2
        TEST = 3
        CLEAN = 5

        def force_generate(self):
            return self == self.DEV or self == self.TEST

        def verify(self):
            return self == self.DEV or self == self.TEST

        def rewrite_hash(self):
            return self == self.DEV

        def ignore_warning(self):
            return self == self.DEV

    rootdir: Path  # /path/to/librar-checker-problems
    basedir: Path  # /path/to/librar-checker-problems/sample/aplusb
    ignore_warning: bool = False

    config: MutableMapping[str, Any]
    checker: Path
    verifier: Path

    def __init__(self, rootdir: Path, basedir: Path):
        self.rootdir = rootdir
        self.basedir = basedir
        tomlpath = basedir / 'info.toml'
        self.config = toml.load(tomlpath) # type: ignore
        self.checker = basedir / \
            self.config.get('checker', 'checker.cpp') # type: ignore
        self.verifier = basedir / \
            self.config.get('verifier', 'verifier.cpp') # type: ignore

    def warning(self, message: str):
        logger.warning(message)
        if not self.ignore_warning:
            raise RuntimeError(message)

    def health_check(self):
        if 'title' not in self.config:
            self.warning('no title: {}'.format(self.basedir))
        for test in self.config['tests']:
            for i in range(test['number']):
                cn = casename(test['name'], i) + '.in'
                if len(cn) > CASENAME_LEN_LIMIT:
                    self.warning('too long casename: {}'.format(cn))

        gendir = self.basedir / 'gen'
        gens: list[str] = []
        for test in self.config['tests']:
            gen = gendir / test['name']
            if gen.suffix == '.cpp':
                gens.append(str(gen))
            elif gen.suffix == '.in':
                for i in range(test['number']):
                    cn = casename(test['name'], i) + '.in'
                    gens.append(str(gendir / cn))
            else:
                logger.error('Unknown file: {}'.format(test['name']))
                raise RuntimeError('Unknown file: {}'.format(test['name']))
        for name in self.basedir.glob('gen/*.cpp'):
            if str(name) not in gens:
                self.warning('Unused .cpp gen file: {}'.format(name))
        for name in self.basedir.glob('gen/*.in'):
            if str(name) not in gens:
                self.warning('Unused .in gen file: {}'.format(name))

    def generate_params_h(self):
        logger.info('generate params.h')
        with open(str(self.basedir / 'params.h'), 'w') as fh:
            for key, value in self.config.get('params', {}).items():
                fh.write(param_to_str(key, value) + '\n')

    def compile_correct(self):
        logger.info('compile solution')
        compile(self.basedir / 'sol' / 'correct.cpp', self.rootdir)

    def compile_verifier(self):
        logger.info('compile verifier')
        compile(self.verifier, self.rootdir)

    def compile_gens(self):
        logger.info('compile generators')
        for test in self.config['tests']:
            name = test['name']
            logger.info('compile {}'.format(name))
            compile(self.basedir / 'gen' / name, self.rootdir)

    def compile_checker(self):
        logger.info('compile checker')
        compile(self.checker, self.rootdir)

    def compile_solutions(self):
        for sol in self.config.get('solutions', []):
            name = sol['name']
            opts = [str(self.basedir / 'grader' / 'grader.cpp'), '-I',
                    str(self.basedir / 'grader')] if sol.get('function', False) else []
            compile(self.basedir / 'sol' / name, self.rootdir, opts)

    def check_all_solutions_used(self) -> bool:
        sol_names: set[str] = set()
        sol_names.add('correct.cpp')
        for sol in self.config.get('solutions', []):
            sol_names.add(sol['name'])

        file_names: set[str] = set()
        file_names.update(p.name for p in (self.basedir / 'sol').glob('*.cpp'))
        file_names.update(p.name for p in (self.basedir / 'sol').glob('*.py'))
        return sol_names == file_names

    def make_inputs(self):
        indir = self.basedir / 'in'
        gendir = self.basedir / 'gen'

        logger.info('clear input {}'.format(indir))
        if indir.exists():
            shutil.rmtree(str(indir))
        indir.mkdir()

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            logger.info('gen {} {}cases'.format(name, num))
            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                check_call_to_file(execcmd(gendir / name, [str(i)]), inpath)

    def verify_inputs(self):
        indir = self.basedir / 'in'

        for test in self.config['tests']:
            name = test['name']
            num = test['number']
            logger.info('verify {} {}cases'.format(name, num))
            for i in range(num):
                inname = (casename(name, i) + '.in')
                inpath = indir / inname
                with open(str(inpath), 'r') as infile:
                    result = run(execcmd(self.verifier),
                                 stdin=infile)
                if result.returncode != 0:
                    logger.error('verify failed: {}'.format(inname))
                    exit(1)

    def make_outputs(self, check: bool):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        soldir = self.basedir / 'sol'
        checker = self.checker

        logger.info('clear output {}'.format(outdir))
        if outdir.exists():
            shutil.rmtree(str(outdir))
        outdir.mkdir()

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                case = casename(name, i)
                inpath = indir / (case + '.in')
                expected = outdir / (case + '.out')
                start = datetime.now()
                with open(str(inpath), 'r') as infile:
                    check_call_to_file(execcmd(soldir / 'correct.cpp'),
                                       expected, stdin=infile)
                end = datetime.now()
                checker_output = bytes()
                if check:
                    process = run(
                        execcmd(checker, [str(inpath), str(expected), str(expected)]), stdout=PIPE, stderr=STDOUT, check=True)
                    checker_output = process.stdout

                logging_result('ANS', start, end,
                               '{} : {}'.format(case, checker_output))

    def is_testcases_already_generated(self) -> bool:
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'

        # get the timestamp when generate.py was last run
        testcases = set()
        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                case = casename(name, i)
                infile = indir / (case + '.in')
                expected = outdir / (case + '.out')
                if not infile.exists() or not expected.exists():
                    return False
                testcases.add(infile)
                testcases.add(expected)

        # Here you should use min, not max. We want ensure that all testcases are newer than all source files.
        latest_timestamp = min(datetime.fromtimestamp(
            path.stat().st_mtime) for path in testcases)

        # compare the timestamp with other files (including header files in common/)
        for path in self.list_depending_files():
            if latest_timestamp < datetime.fromtimestamp(path.stat().st_mtime):
                return False
        logger.info('Test cases are already generated')
        return True

    def is_checker_already_generated(self) -> bool:
        checker_bin = self.checker.parent / self.checker.stem
        if platform.system() == 'Windows':
            checker_bin = checker_bin.with_suffix('.exe')
        if not checker_bin.exists():
            return False

        checker_timestamp = datetime.fromtimestamp(checker_bin.stat().st_mtime)
        for path in self.list_depending_files():
            if checker_timestamp < datetime.fromtimestamp(path.stat().st_mtime):
                return False
        logger.info('The checker is already compiled')
        return True

    def list_depending_files(self) -> Iterator[Path]:
        yield Path(__file__)
        for path in list(self.basedir.glob('**/*')) + list(self.rootdir.glob('common/**/*')):
            if (self.basedir / 'in').exists() and (self.basedir / 'in').resolve() in path.resolve().parents:
                continue
            if (self.basedir / 'out').exists() and (self.basedir / 'out').resolve() in path.resolve().parents:
                continue
            if not path.is_file():
                continue  # ignore directories
            if path.suffix == ('' if platform.system() != 'Windows' else '.exe'):
                continue  # ignore compiled binaries
            if path.name == 'params.h':
                continue  # ignore generated params.h
            yield path

    # return "version" of problem
    def problem_version(self) -> str:
        hashes: List[bytes] = list()
        for path in self.list_depending_files():
            with path.open('rb') as f:
                hashes.append(hashlib.sha256(f.read()).digest())
        all_hash = hashlib.sha256()
        for h in sorted(hashes):
            all_hash.update(h)
        return all_hash.hexdigest()

    def judge(self, src: Path, config: dict):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        _tmpdir = TemporaryDirectory()
        tmpdir = _tmpdir.name
        checker = self.checker
        results: set[str] = set()

        logger.info('Start {}'.format(src.name))

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                case = casename(name, i)
                inpath = indir / (case + '.in')
                expected = outdir / (case + '.out')
                actual = Path(tmpdir) / (case + '.out')

                start = datetime.now()
                result = ''
                checker_output = bytes()
                try:
                    with open(str(inpath), 'r') as infile:
                        check_call_to_file(execcmd(src), actual,
                                           stdin=infile, timeout=self.config['timelimit'])
                except TimeoutExpired:
                    result = 'TLE'
                except CalledProcessError:
                    result = 'RE'
                else:
                    process = run(
                        execcmd(checker, [str(inpath), str(actual), str(expected)]), stdout=PIPE, stderr=STDOUT)
                    checker_output = process.stdout
                    if process.returncode:
                        result = 'WA'
                    else:
                        result = 'AC'
                end = datetime.now()

                results.add(result)
                logging_result(result, start, end,
                               '{} : {}'.format(case, checker_output.decode('utf-8')))

        _tmpdir.cleanup()
        expect_status: str = config.get('expect', '')  # type: ignore
        allow_status: set[str] = set()
        if expect_status != "":
            allow_status.add(expect_status)
        allow_status.add('AC')
        if config.get('allow_wa', False):
            allow_status.add('WA')
        if config.get('allow_re', False):
            allow_status.add('RE')
        if config.get('allow_tle', False):
            allow_status.add('TLE')

        if len(results - allow_status) != 0:
            logger.error('unexpected status was appeared: {} (allowed {})'.format(
                results, allow_status))
        if expect_status != '' and expect_status not in results:
            logger.error('expected status {} was not appeared: {}'.format(
                expect_status, results))

    def calc_hashes(self) -> MutableMapping[str, str]:
        hashes: MutableMapping[str, str] = dict()
        for name in self.basedir.glob('in/*.in'):
            m = hashlib.sha256()
            with open(str(name), 'rb') as f:
                m.update(f.read())
            hashes[name.name] = m.hexdigest()
        for name in self.basedir.glob('out/*.out'):
            m = hashlib.sha256()
            with open(str(name), 'rb') as f:
                m.update(f.read())
            hashes[name.name] = m.hexdigest()
        return hashes

    def assert_hashes(self):
        if not Path(self.basedir, 'hash.json').exists():
            raise RuntimeError("hash.json doesn't exist")
        with open(str(self.basedir / 'hash.json'), 'r') as f:
            expect = json.load(f)
        actual = self.calc_hashes()
        if expect != actual:
            logger.error('hashes are different')
            logger.error('your hash: {}'.format(
                json.dumps(actual, indent=2, sort_keys=True)))
            raise RuntimeError("hashes are different")

    def write_hashes(self):
        hashpath: Path = self.basedir / 'hash.json'
        actual = self.calc_hashes()
        if not Path(self.basedir, 'hash.json').exists():
            self.warning("hash.json doesn't exist, create")
        else:
            with hashpath.open('r') as f:
                expect = json.load(f)
                if expect != actual:
                    self.warning('hashes are different, overwrite')
                    self.warning('your hash: {}'.format(
                        json.dumps(actual, indent=2, sort_keys=True)))
        with hashpath.open('w') as f:
            json.dump(self.calc_hashes(), f, indent=2, sort_keys=True)

    def clean(self):
        if (self.basedir / 'in').exists():
            shutil.rmtree(self.basedir / 'in')
        if (self.basedir / 'out').exists():
            shutil.rmtree(self.basedir / 'out')

    def generate(self, mode: Mode):
        if mode == self.Mode.DEV:
            self.ignore_warning = True

        logger.info('Start {}'.format(self.basedir.name))

        # health check
        self.health_check()

        self.generate_params_h()

        if mode == self.Mode.CLEAN:
            logger.info('Cleaning input & output directory of {}'.format(
                self.basedir.name))
            self.clean()
            return

        is_testcases_already_generated = self.is_testcases_already_generated()
        is_checker_already_generated = self.is_checker_already_generated()

        if not is_checker_already_generated or mode.force_generate():
            self.compile_checker()

        if not is_testcases_already_generated or mode.force_generate():
            self.compile_correct()
            self.compile_gens()
            self.make_inputs()

        if mode.verify():
            self.compile_verifier()
            self.verify_inputs()

        if not is_testcases_already_generated or mode.force_generate():
            self.make_outputs(mode.verify())

        if mode.verify():
            self.compile_solutions()
            for sol in self.config.get('solutions', []):
                self.judge(self.basedir / 'sol' / sol['name'], sol)
            if not self.check_all_solutions_used():
                self.warning('Some solutions are not used')

        if mode.rewrite_hash():
            self.write_hashes()
        else:
            self.assert_hashes()


def main(args: List[str]):
    try:
        import colorlog
    except ImportError:
        basicConfig(
            format="%(asctime)s [%(levelname)s] %(message)s",
            datefmt="%H:%M:%S",
            level=getenv('LOG_LEVEL', 'INFO'),
        )
        logger.warn('Please install colorlog: pip3 install colorlog')
    else:
        handler = colorlog.StreamHandler()
        formatter = colorlog.ColoredFormatter(
            "%(log_color)s%(asctime)s [%(levelname)s] %(message)s",
            datefmt="%H:%M:%S",
            log_colors={
                'DEBUG':    'cyan',
                'INFO':     'white',
                'WARNING':  'yellow',
                'ERROR':    'red',
                'CRITICAL': 'red,bg_white',
            })
        handler.setFormatter(formatter)
        basicConfig(
            level=getenv('LOG_LEVEL', 'INFO'),
            handlers=[handler]
        )

    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('toml', nargs='*', help='Toml File')
    parser.add_argument('-p', '--problem', nargs='*',
                        help='Generate problem', default=[])

    parser.add_argument('--dev', action='store_true', help='Developer Mode')
    parser.add_argument('--test', action='store_true', help='CI Mode')
    parser.add_argument('--clean', action='store_true', help='Clean in/out')
    parser.add_argument('--compile-checker',
                        action='store_true', help='Deprecated: Compile Checker')

    opts = parser.parse_args(args)

    if opts.dev + opts.test + opts.clean >= 2:
        raise ValueError('at most one of --dev, --test, --clean can be used')

    if opts.compile_checker:
        logger.warning(
            '--compile-checker is deprecated. Checker is compiled in default')

    rootdir: Path = Path(__file__).parent
    problems: List[Problem] = list()

    for tomlpath in opts.toml:
        problems.append(Problem(rootdir, Path(tomlpath).parent))

    for problem_name in opts.problem:
        problem_dir = find_problem_dir(rootdir, problem_name)
        if problem_dir is None:
            raise ValueError('Cannot find problem: {}'.format(problem_name))
        problems.append(Problem(rootdir, problem_dir))

    if len(problems) == 0:
        logger.warning('No problems')

    # suppress the annoying dialog appears when an application crashes on Windows
    if platform.uname().system == 'Windows':
        import ctypes
        # https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        SEM_NOGPFAULTERRORBOX = 2
        ctypes.windll.kernel32.SetErrorMode(  # type: ignore
            SEM_NOGPFAULTERRORBOX)

    mode = Problem.Mode.DEFAULT
    if opts.dev:
        mode = Problem.Mode.DEV
    if opts.test:
        mode = Problem.Mode.TEST
    if opts.clean:
        mode = Problem.Mode.CLEAN

    for problem in problems:
        problem.generate(mode)


if __name__ == '__main__':
    main(sys.argv[1:])
