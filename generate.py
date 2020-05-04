#!/usr/bin/env python3

import sys
import argparse
import os
import platform
import shutil
import hashlib
import json
from datetime import datetime
from logging import Logger, basicConfig, getLogger
from os import getenv
from pathlib import Path
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
                        TimeoutExpired, call, check_call, check_output, run)
from tempfile import TemporaryDirectory
from typing import Any, Iterator, List, MutableMapping, Union

import toml

logger = getLogger(__name__)  # type: Logger


def casename(name: Union[str, Path], i: int) -> str:
    # (random, 1) -> random_01
    return Path(name).stem + '_' + str(i).zfill(2)


class UnknownTypeFile(Exception):
    def __init__(self, message):
        super().__init__()
        self.message = message


def compile(src: Path, libdir: Path):
    if src.suffix == '.cpp':
        cxx = getenv('CXX', 'g++')
        cxxflags_default = '-O2 -std=c++14 -Wall -Wextra -Werror -Wno-unused-result'
        if platform.system() == 'Darwin':
            cxxflags_default += ' -Wl,-stack_size,0x10000000'  # 256MB
        if platform.system() == 'Windows':
            cxxflags_default += ' -Wl,-stack,0x10000000'  # 256MB
            cxxflags_default += ' -D__USE_MINGW_ANSI_STDIO' # avoid using MinGW's "unique" stdio, which doesn't recognize %lld
        if platform.uname().system == 'Linux' and 'Microsoft' in platform.uname().release:
            cxxflags_default += ' -fsplit-stack'  # a workaround for the lack of ulimit in Windows Subsystem for Linux
        cxxflags = getenv('CXXFLAGS', cxxflags_default).split()
        cxxflags.extend(['-I', str(libdir / 'common')])
        check_call([cxx] + cxxflags +
                   ['-o', str(src.with_suffix(''))] + [str(src)])
    elif src.suffix == '.in':
        pass
    else:
        logger.error('Unknown type of file {}'.format(src))
        raise UnknownTypeFile('Unknown file: {}'.format(src))


def execcmd(src: Path, arg: List[str] = []) -> List[str]:
    # main.cpp -> ['main']
    # example.in -> ['cat', 'example_00.in']
    if src.suffix == '.cpp':
        cmd = [str(src.with_suffix('' if platform.system() != 'Windows' else '.exe').resolve())]
        cmd.extend(arg)
        return cmd
    elif src.suffix == '.in':
        inpath = src.with_name(casename(src, int(arg[0])) + '.in')
        if platform.system() == 'Windows': cmd = ['cmd', '/C', 'type', str(inpath)] # Windows' built-in command 
        else: cmd = ['cat', str(inpath)]
        return cmd
    else:
        raise UnknownTypeFile('Unknown file: {} {}'.format(src, arg))


def check_call_to_file(command: List[str], outpath: Path, *args, **kwargs):
    # same as subprocess.check_call(command, stdout=open(outpath, "w"), *args, **kwargs)
    # but handles CRLF stuff on Windows
    if platform.uname().system == 'Windows':
        result = run(command, stdout=PIPE, check=True, *args, **kwargs)
        with open(str(outpath), "w", newline='\n') as out_file:
            out_file.write(result.stdout.decode('utf-8').replace(os.linesep, '\n'))
    else:
        check_call(command, stdout=open(str(outpath), "w"), *args, **kwargs)


def logging_result(result: str, start: datetime, end: datetime, message: str):
    usemsec = (end - start).seconds*1000 + \
        (end - start).microseconds // 1000
    logger.info('{:>3s} {:6d} msecs : {}'.format(
        result, usemsec, message))


class Problem:
    def __init__(self, libdir: Path, basedir: Path):
        self.libdir = libdir  # type: Path
        self.basedir = basedir  # type: Path
        tomlpath = basedir / 'info.toml'
        self.config = toml.load(tomlpath)  # type: MutableMapping[str, Any]
        self.checker = basedir / self.config.get('checker', 'checker.cpp')  # type: Path
        self.verifier = basedir / self.config.get('verifier', 'verifier.cpp')  # type: Path

    def health_check(self):
        if 'title' not in self.config:
            logger.error('no title: {}'.format(self.basedir))
            exit(1)
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
                raise UnknownTypeFile('Unknown file: {}'.format(test['name']))
        for name in self.basedir.glob('gen/*.cpp'):
            if str(name) not in gens:
                logger.error('Unused .cpp gen file: {}'.format(name))
                exit(1)
        for name in self.basedir.glob('gen/*.in'):
            if str(name) not in gens:
                logger.error('Unused .in gen file: {}'.format(name))
                exit(1)

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
        compile(self.basedir / 'sol' / 'correct.cpp', self.libdir)

    def compile_verifier(self):
        logger.info('compile verifier')
        compile(self.verifier, self.libdir)

    def compile_gens(self):
        logger.info('compile generators')
        for test in self.config['tests']:
            name = test['name']
            logger.info('compile {}'.format(name))
            compile(self.basedir / 'gen' / name, self.libdir)

    def compile_checker(self):
        logger.info('compile checker')
        compile(self.checker, self.libdir)

    def compile_solutions(self):
        for sol in self.config.get('solutions', []):
            name = sol['name']
            compile(self.basedir / 'sol' / name, self.libdir)

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
                check_call_to_file(execcmd(soldir / 'correct.cpp'), expected, stdin=open(str(infile), 'r'))
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
        for path in list(self.basedir.glob('**/*')) + list(self.libdir.glob('common/**/*')):
            if (self.basedir / 'in').exists() and (self.basedir / 'in').resolve() in path.resolve().parents:
                continue
            if (self.basedir / 'out').exists() and (self.basedir / 'out').resolve() in path.resolve().parents:
                continue
            if not path.is_file():
                continue # ignore directories
            if path.suffix == '':
                continue  # ignore compiled binaries
            if path.name.endswith('.html'):
                continue  # ignore generated HTML files
            if path.name == 'params.h':
                continue  # ignore generated params.h
            yield path

    # return "version" of problem
    def problem_version(self) -> str:
        all_hash = hashlib.sha256()
        for path in sorted(self.list_depending_files()):
            all_hash.update(hashlib.sha256(open(str(path), 'rb').read()).digest())
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

    def write_html(self, htmldir: Path):
        from htmlgen import ToHTMLConverter
        # convert task
        html = self.gen_html()
        path = self.basedir / 'task.html' if not htmldir else htmldir / \
            (self.basedir.name + '.html')
        with open(str(path), 'w', encoding='utf-8') as f:
            f.write(html.html)

    def calc_hashes(self) -> MutableMapping[str, str]:
        hashes = dict()  # type: MutableMapping[str, str]
        for name in self.basedir.glob('in/*.in'):
            m = hashlib.sha256()
            m.update(open(str(name), 'rb').read())
            hashes[name.name] = m.hexdigest()
        for name in self.basedir.glob('out/*.out'):
            m = hashlib.sha256()
            m.update(open(str(name), 'rb').read())
            hashes[name.name] = m.hexdigest()
        return hashes

    def check_hashes(self):
        if not Path(self.basedir, 'hash.json').exists():
            logger.error("hash.json doesn't exist")
            exit(1)
        expect = json.load(open(str(self.basedir / 'hash.json'), 'r'))
        actual = self.calc_hashes()
        if expect != actual:
            logger.error('hashes are different')
            logger.error('your hash: {}'.format(
                json.dumps(actual, indent=2, sort_keys=True)))
            exit(1)

    def write_hashes(self):
        json.dump(self.calc_hashes(), open(
            str(self.basedir / 'hash.json'), 'w'), indent=2, sort_keys=True)


def generate(
        problem: Problem,
        force_generate: bool,
        rewrite_hash: bool,
        verify: bool,
        compile_checker: bool,
        generate_html: bool,
        html_dir: Union[Path, None]):
    # health check
    problem.health_check()

    logger.info('Start {}'.format(problem.basedir.name))

    is_testcases_already_generated = problem.is_testcases_already_generated()
    is_checker_already_generated = problem.is_checker_already_generated()

    problem.generate_params_h()

    if not is_testcases_already_generated or force_generate:
        problem.compile_correct()
        problem.compile_gens()
        problem.make_inputs()

    if verify:
        problem.compile_verifier()
        problem.verify_inputs()

    if verify or compile_checker:
        if not is_checker_already_generated or force_generate:
            problem.compile_checker()

    if not is_testcases_already_generated or force_generate:
        problem.make_outputs(verify)

    if verify:
        problem.compile_solutions()
        # TODO: problem.judge_solutions()?
        for sol in problem.config.get('solutions', []):
            problem.judge(problem.basedir / 'sol' / sol['name'], sol)

    if rewrite_hash:
        problem.write_hashes()
    else:
        problem.check_hashes()

    if generate_html:
        problem.write_html(html_dir if html_dir else problem.basedir)


def main(args: List[str]):
    basicConfig(
        level=getenv('LOG_LEVEL', 'INFO'),
        format="%(asctime)s [%(levelname)s] %(message)s"
    )
    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('toml', nargs='*', help='Toml File')
    parser.add_argument('-p', '--problem', nargs='*',
                        help='Generate problem', default=[])
    parser.add_argument('--verify', action='store_true', help='Verify Inputs')
    parser.add_argument('--html', action='store_true', help='Generate HTML')
    parser.add_argument('--refhash', action='store_true', help='Refresh Hash')
    parser.add_argument(
        '--ignore-cache', action='store_true', help='Ignore cache')
    parser.add_argument('--compile-checker',
                        action='store_true', help='Compile Checker')

    parser.add_argument('--nogen', action='store_true', help='Skip Generate')
    parser.add_argument('--sol', action='store_true', help='Solution Test')
    parser.add_argument('--htmldir', help='Generate HTML', default=None)
    opts = parser.parse_args(args)

    if opts.nogen:
        logger.warning(
            '--nogen is deprecated, because auto skip was implemented')
    if opts.sol:
        logger.warning(
            '--sol is deprecated. --sol is also enabled by --verify')

    libdir = Path(__file__).parent
    problems = list()  # type: List[Problem]

    for tomlpath in opts.toml:
        tomlfile = toml.load(opts.toml)
        if 'problems' in tomlfile:
            logger.warning('problems.toml is deprecated')
            continue
        problems.append(Problem(libdir, Path(tomlpath).parent))

    for problem_name in opts.problem:
        tomls = list(libdir.glob('**/{}/info.toml'.format(problem_name)))
        if len(tomls) == 0:
            logger.error('Cannot find problem: {}'.format(problem_name))
            exit(1)
        if len(tomls) >= 2:
            logger.error('Find multi problem dirs: {}'.format(problem_name))
            exit(1)
        problem_dir = tomls[0].parent
        problems.append(Problem(libdir, problem_dir))
        logger.info('Find problem dir {}'.format(problem_dir))

    if len(problems) == 0:
        logger.warning('No problems')

    if opts.htmldir:
        logger.info('make htmldir')
        Path(opts.htmldir).mkdir(exist_ok=True, parents=True)
    
    # suppress the annoying dialog appears when an application crashes on Windows
    if platform.uname().system == 'Windows':
        import ctypes 
        SEM_NOGPFAULTERRORBOX = 2 # https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        ctypes.windll.kernel32.SetErrorMode(SEM_NOGPFAULTERRORBOX)

    for problem in problems:
        generate(problem, opts.ignore_cache, opts.refhash, opts.verify, opts.compile_checker, opts.html,
                 Path(opts.htmldir) if opts.htmldir else None)


if __name__ == '__main__':
    main(sys.argv[1:])
