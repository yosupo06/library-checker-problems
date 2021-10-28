#!/usr/bin/env python3

import sys
import argparse
import os
import platform
import shutil
import hashlib
import json
from datetime import datetime
from logging import Logger, basicConfig, getLogger, INFO
from os import getenv
from pathlib import Path
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
                        TimeoutExpired, call, check_call, check_output, run)
from tempfile import TemporaryDirectory
from typing import Any, Iterator, List, MutableMapping, Union, Optional

from enum import Enum
import toml

logger = getLogger(__name__)  # type: Logger

CASENAME_LEN_LIMIT = 40
STACK_SIZE = 2 ** 31  # 2GB


def casename(name: Union[str, Path], i: int) -> str:
    """(random, 1) -> random_01"""
    return Path(name).stem + '_' + str(i).zfill(2)


def compile(src: Path, rootdir: Path):
    if src.suffix == '.cpp':
        cxx = getenv('CXX', 'g++')
        cxxflags_default = '-O2 -std=c++17 -Wall -Wextra -Werror -Wno-unused-result'
        if platform.system() == 'Darwin':
            cxxflags_default += ' -Wl,-stack_size,{}'.format(hex(STACK_SIZE))
        if platform.system() == 'Windows':
            cxxflags_default += ' -Wl,-stack,{}'.format(hex(STACK_SIZE))
            # avoid using MinGW's "unique" stdio, which doesn't recognize %lld
            cxxflags_default += ' -D__USE_MINGW_ANSI_STDIO'
        if platform.uname().system == 'Linux' and 'Microsoft' in platform.uname().release:
            # a workaround for the lack of ulimit in Windows Subsystem for Linux
            cxxflags_default += ' -fsplit-stack'
        cxxflags = getenv('CXXFLAGS', cxxflags_default).split()
        cxxflags.extend(['-I', str(rootdir / 'common')])
        check_call([cxx] + cxxflags +
                   ['-o', str(src.with_suffix(''))] + [str(src)])
    elif src.suffix == '.in':
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
    elif src.suffix == '.in':
        inpath = src.with_name(casename(src, int(arg[0])) + '.in')
        if platform.system() == 'Windows':
            # Windows' built-in command
            cmd = ['cmd', '/C', 'type', str(inpath)]
        else:
            cmd = ['cat', str(inpath)]
        return cmd
    else:
        raise RuntimeError('Unknown file: {} {}'.format(src, arg))


def check_call_to_file(command: List[str], outpath: Path, *args, **kwargs):
    # same as subprocess.check_call(command, stdout=open(outpath, "w"), *args, **kwargs)
    # but handles CRLF stuff on Windows
    if platform.uname().system == 'Windows':
        result = run(command, stdout=PIPE, check=True, *args, **kwargs)
        with open(str(outpath), "w", newline='\n') as out_file:
            out_file.write(result.stdout.decode(
                'utf-8').replace(os.linesep, '\n'))
    else:
        check_call(command, stdout=open(str(outpath), "w"), *args, **kwargs)


def logging_result(result: str, start: datetime, end: datetime, message: str):
    elapsed_millis = (end - start).seconds*1000 + \
        (end - start).microseconds // 1000
    logger.info('{:>3s} {:6d} msecs : {}'.format(
        result, elapsed_millis, message))


class Problem:
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
        self.config = toml.load(tomlpath)
        self.checker = basedir / \
            self.config.get('checker', 'checker.cpp')
        self.verifier = basedir / \
            self.config.get('verifier', 'verifier.cpp')

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
        gens = []
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
                if isinstance(value, int):
                    fh.write('#define {} (long long){}\n'.format(key, value))
                elif isinstance(value, float):
                    fh.write('#define {} {}\n'.format(key, value))
                elif isinstance(value, str):
                    # NOTE: this fails if value contains some chars like double quotations
                    fh.write('#define {} "{}"\n'.format(key, value))
                else:
                    logger.error('Unsupported type of params: {}'.format(key))
                    exit(1)

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
            compile(self.basedir / 'sol' / name, self.rootdir)

    def check_all_solutions_used(self) -> bool:
        sol_names = []
        sol_names.append('correct.cpp')
        for sol in self.config.get('solutions', []):
            sol_names.append(sol['name'])
        for file_path in (self.basedir / 'sol').glob('*.cpp'):
            if file_path.name not in sol_names:
                return False
        return True

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
                result = run(execcmd(self.verifier),
                             stdin=open(str(inpath), 'r'))
                if result.returncode != 0:
                    logger.error('verify failed: {}'.format(inname))
                    exit(1)

    def make_outputs(self, check):
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
                infile = indir / (case + '.in')
                expected = outdir / (case + '.out')
                start = datetime.now()
                check_call_to_file(execcmd(soldir / 'correct.cpp'),
                                   expected, stdin=open(str(infile), 'r'))
                end = datetime.now()
                checker_output = bytes()
                if check:
                    process = run(
                        execcmd(checker, [str(infile), str(expected), str(expected)]), stdout=PIPE, stderr=STDOUT, check=True)
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
            if path.suffix == '':
                continue  # ignore compiled binaries
            if path.name.endswith('.html'):
                continue  # ignore generated HTML files
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

    # return "version" of testcase
    def testcase_version(self) -> str:
        all_hash = hashlib.sha256()
        all_hash.update(hashlib.sha256(
            open(str(self.checker), 'rb').read()).digest())
        cases = json.load(open(str(self.basedir / 'hash.json'), 'r'))
        for name, sha in sorted(cases.items(), key=lambda x: x[0]):
            all_hash.update(sha.encode('ascii'))
        return all_hash.hexdigest()

    def judge(self, src: Path, config: dict):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        _tmpdir = TemporaryDirectory()
        tmpdir = _tmpdir.name
        checker = self.checker
        results = set()

        logger.info('Start {}'.format(src.name))

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                case = casename(name, i)
                infile = indir / (case + '.in')
                expected = outdir / (case + '.out')
                actual = Path(tmpdir) / (case + '.out')

                start = datetime.now()
                result = ''
                checker_output = bytes()
                try:
                    check_call_to_file(execcmd(src), actual,
                                       stdin=open(str(infile), 'r'), timeout=self.config['timelimit'])
                except TimeoutExpired:
                    result = 'TLE'
                except CalledProcessError:
                    result = 'RE'
                else:
                    process = run(
                        execcmd(checker, [str(infile), str(actual), str(expected)]), stdout=PIPE, stderr=STDOUT)
                    checker_output = process.stdout
                    if process.returncode:
                        result = 'WA'
                    else:
                        result = 'AC'
                end = datetime.now()

                results.add(result)
                logging_result(result, start, end,
                               '{} : {}'.format(case, checker_output.decode('utf-8')))

        if config.get('wrong', False):
            if results == {'AC'}:
                logger.error('wrong solution got accept: {}'.format(src))
                exit(1)
        else:
            if 'WA' in results or 'RE' in results:
                logger.error('correct solution got wa/re: {}'.format(src))
                exit(1)
            if not config.get('allow_tle', False) and 'TLE' in results:
                logger.error('fast solution got tle: {}'.format(src))
                exit(1)

    def gen_html(self):
        from htmlgen import ToHTMLConverter
        # convert task
        return ToHTMLConverter(self.basedir, self.config)

    def write_html(self, htmldir: Optional[Path]):
        # convert task
        html = self.gen_html()
        if not html.check_all_samples_used():
            self.warning('all samples are not used')
        path = (self.basedir / 'task.html') if not htmldir else htmldir / \
            (self.basedir.resolve().name + '.html')
        with open(str(path), 'w', encoding='utf-8') as f:
            f.write(html.html)

    def calc_hashes(self) -> MutableMapping[str, str]:
        hashes: MutableMapping[str, str] = dict()
        for name in self.basedir.glob('in/*.in'):
            m = hashlib.sha256()
            m.update(open(str(name), 'rb').read())
            hashes[name.name] = m.hexdigest()
        for name in self.basedir.glob('out/*.out'):
            m = hashlib.sha256()
            m.update(open(str(name), 'rb').read())
            hashes[name.name] = m.hexdigest()
        return hashes

    def assert_hashes(self):
        if not Path(self.basedir, 'hash.json').exists():
            raise RuntimeError("hash.json doesn't exist")
        expect = json.load(open(str(self.basedir / 'hash.json'), 'r'))
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

    class Mode(Enum):
        DEFAULT = 1
        DEV = 2
        TEST = 3
        HTML = 4
        CLEAN = 5

        def force_generate(self):
            return self == self.DEV or self == self.TEST

        def verify(self):
            return self == self.DEV or self == self.TEST

        def rewrite_hash(self):
            return self == self.DEV

        def generate_html(self):
            return self == self.DEV or self == self.TEST

    def generate(self, mode: Mode, html_dir: Optional[Path]):
        if mode == self.Mode.DEV:
            self.ignore_warning = True

        logger.info('Start {}'.format(self.basedir.name))

        # health check
        self.health_check()

        self.generate_params_h()

        if mode == self.Mode.CLEAN:
            logger.info('Clean input & output directry of {}'.format(
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

        if mode == self.Mode.HTML:
            logger.info('HTML generator Mode, skip judge')
            self.write_html(html_dir)
            return

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

        if mode.generate_html():
            self.write_html(html_dir)


def find_problem_dir(rootdir: Path, problem_name: Path) -> Optional[Path]:
    tomls = list(rootdir.glob('**/{}/info.toml'.format(problem_name)))
    if len(tomls) == 0:
        logger.error('Cannot find problem: {}'.format(problem_name))
        return None
    if len(tomls) >= 2:
        logger.error('Find multiple problem dirs: {}'.format(problem_name))
        return None
    return tomls[0].parent
