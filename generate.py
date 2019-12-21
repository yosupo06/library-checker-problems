#!/usr/bin/env python3

import argparse
import os
import platform
import shutil
from datetime import datetime
from logging import Logger, basicConfig, getLogger
from os import getenv
from pathlib import Path
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
                        TimeoutExpired, call, check_call, check_output, run)
from tempfile import TemporaryDirectory
from typing import Any, List, MutableMapping, Union

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
        cxxflags_default = '-O2 -std=c++14 -Wall -Wextra -Werror'
        if platform.system() == 'Darwin':
            cxxflags_default += ' -Wl,-stack_size,0x10000000'  # 256MB
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
        cmd = [str(src.with_suffix('').resolve())]
        cmd.extend(arg)
        return cmd
    elif src.suffix == '.in':
        inpath = src.with_name(casename(src, int(arg[0])) + '.in')
        cmd = ['cat', str(inpath)]
        return cmd
    else:
        raise UnknownTypeFile('Unknown file: {} {}'.format(src, arg))


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

    def health_check(self):
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

    def compile_correct(self):
        logger.info('compile solution')
        compile(self.basedir / 'sol' / 'correct.cpp', self.libdir)

    def compile_verifier(self):
        logger.info('compile verifier')
        compile(self.basedir / 'verifier.cpp', self.libdir)

    def compile_gens(self):
        logger.info('compile generators')
        for test in self.config['tests']:
            name = test['name']
            logger.info('compile {}'.format(name))
            compile(self.basedir / 'gen' / name, self.libdir)

    def compile_checker(self):
        logger.info('compile checker')
        compile(self.basedir / 'checker.cpp', self.libdir)

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

            logger.info('case {} {}cases'.format(name, num))
            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                check_call(
                    execcmd(gendir / name, [str(i)]), stdout=open(str(inpath), 'w'))

    def verify_inputs(self):
        indir = self.basedir / 'in'

        for test in self.config['tests']:
            name = test['name']
            num = test['number']
            logger.info('case {} {}cases'.format(name, num))
            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                check_call(
                    execcmd(self.basedir / 'verifier.cpp'), stdin=open(str(inpath), 'r'))

    def make_outputs(self, check):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        soldir = self.basedir / 'sol'
        checker = self.basedir / 'checker.cpp'

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
                check_call(execcmd(soldir / 'correct.cpp'),
                           stdin=open(str(infile), 'r'), stdout=open(str(expected), 'w'))
                end = datetime.now()
                checker_output = bytes()
                if check:
                    process = run(
                        execcmd(checker, [str(infile), str(expected), str(expected)]), stdout=PIPE, stderr=STDOUT, check=True)
                    checker_output = process.stdout

                logging_result('ANS', start, end,
                               '{} : {}'.format(case, checker_output))

    def is_already_generated(self) -> bool:
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

        latest_timestamp = min(datetime.fromtimestamp(path.stat().st_mtime) for path in testcases)  # Here you should use min, not max. We want ensure that all testcases are newer than all source files.

        # compare the timestamp with other files (including header files in common/)
        for path in list(self.basedir.glob('**/*')) + list(self.libdir.glob('common/**/*')):
            if path in testcases:
                continue
            if not path.is_file():
                continue
            if os.access(str(path), os.X_OK):
                continue  # ignore directries and compiled binaries
            if path.name.endswith('.html'):
                continue  # ignore generated HTML files
            if latest_timestamp < datetime.fromtimestamp(path.stat().st_mtime):
                return False
        logger.info('Test cases are already generated')
        return True

    def judge(self, src: Path, config: dict):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        _tmpdir = TemporaryDirectory()
        tmpdir = _tmpdir.name
        checker = self.basedir / 'checker.cpp'
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
                    check_call(execcmd(src), stdin=open(str(infile), 'r'), stdout=open(
                        str(actual), 'w'), timeout=self.config['timelimit'])
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
                               '{} : {}'.format(case, checker_output))

        expectaccept = not config.get('wrong', False)
        actualaccept = (results == {'AC'})
        if expectaccept != actualaccept:
            logger.error('Fail {} : expect_accept = {} : results = {}'.format(
                src, expectaccept, results))
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


if __name__ == '__main__':
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('toml', type=argparse.FileType('r'), help='Toml File')
    parser.add_argument('-p', '--problem', nargs='*',
                        help='Generate problem', default=[])
    parser.add_argument('--nogen', action='store_true', help='Skip Generate')
    parser.add_argument('--verify', action='store_true', help='Verify Inputs')
    parser.add_argument('--sol', action='store_true', help='Solution Test')
    parser.add_argument('--html', action='store_true', help='Generate HTML')
    parser.add_argument('--htmldir', help='Generate HTML', default=None)
    parser.add_argument('--ignore-cache', action='store_true', help='Ignore cache')
    args = parser.parse_args()

    problems = toml.load(args.toml)
    libdir = Path(args.toml.name).parent
    targetprobs = set(args.problem)

    probs = dict()

    if args.htmldir:
        logger.info('mkdir htmldir')
        Path(args.htmldir).mkdir(exist_ok=True)

    for name in targetprobs:
        if name not in problems['problems']:
            logger.error('There is not problem {}'.format(name))
            exit(1)

    for name, probinfo in problems['problems'].items():
        if targetprobs and name not in targetprobs:
            continue

        problem = Problem(libdir, libdir / probinfo['dir'])
        probs[name] = problem

        # health check
        problem.health_check()

        logger.info('Start {}'.format(probinfo['dir']))

        is_already_generated = problem.is_already_generated()

        if not args.nogen and (not is_already_generated or args.ignore_cache):
            problem.compile_correct()
            problem.compile_gens()
            problem.make_inputs()

        if args.verify:
            problem.compile_verifier()
            problem.verify_inputs()

        if args.sol:
            problem.compile_checker()

        if not args.nogen and (args.sol or not is_already_generated or args.ignore_cache):
            problem.make_outputs(args.sol)

        if args.sol:
            problem.compile_solutions()
            for sol in problem.config.get('solutions', []):
                problem.judge(problem.basedir / 'sol' / sol['name'], sol)

        if args.html:
            problem.write_html(Path(args.htmldir)
                               if args.htmldir else problem.basedir)
