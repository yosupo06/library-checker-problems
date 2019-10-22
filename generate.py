#!/usr/bin/env python3

import argparse
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
        # type: MutableMapping[str, Any]
        self.config = toml.load(basedir / 'info.toml')

    def compile_correct(self):
        logger.info('compile solution')
        compile(self.basedir / 'sol' / 'correct.cpp', self.libdir)

    def compile_verify(self):
        logger.info('compile verify')
        compile(self.basedir / 'verify.cpp', self.libdir)

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
        gendir = self.basedir / 'gen'

        for test in self.config['tests']:
            name = test['name']
            num = test['number']
            logger.info('case {} {}cases'.format(name, num))
            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                check_call(
                    execcmd(gendir / self.config['verify']), stdin=open(str(inpath), 'r'))

    def make_outputs(self):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        soldir = self.basedir / 'sol'

        logger.info('clear output {}'.format(outdir))
        if outdir.exists():
            shutil.rmtree(str(outdir))
        outdir.mkdir()

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                outpath = outdir / (casename(name, i) + '.out')
                start = datetime.now()
                check_call(execcmd(soldir / self.config['solution']),
                           stdin=open(str(inpath), 'r'), stdout=open(str(outpath), 'w'))
                end = datetime.now()
                logging_result('ANS', start, end, '{}'.format(casename(name, i)))

    def judge(self, src: Path, config: dict):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        _tmpdir = TemporaryDirectory()
        tmpdir = _tmpdir.name
        checker = self.basedir / 'checker.cpp'
        results = set()

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

    def gen_html(self, htmldir: Path):
        from htmlgen import ToHTMLConverter
        # convert task
        logger.info('generate doc')
        html = ToHTMLConverter(self.basedir)
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
    args = parser.parse_args()

    problems = toml.load(args.toml)
    libdir = Path(args.toml.name).parent
    targetprobs = set(args.problem)

    probs = dict()

    if args.htmldir:
        logger.info('mkdir htmldir')
        Path(args.htmldir).mkdir(exist_ok=True)

    for name, probinfo in problems['problems'].items():
        if targetprobs and name not in targetprobs:
            continue

        problem = Problem(libdir, libdir / probinfo['dir'])
        probs[name] = problem

        logger.info('Start {}'.format(probinfo['dir']))

        if not args.nogen:
            problem.compile_correct()
            problem.compile_gens()
            problem.make_inputs()

        if args.verify:
            problem.compile_verify()
            problem.verify_inputs()

        if not args.nogen:
            problem.make_outputs()

        if args.sol:
            problem.compile_checker()
            problem.compile_solutions()
            for sol in problem.config.get('solutions', []):
                problem.judge(problem.basedir / 'sol' / sol['name'], sol)

        if args.html:
            problem.gen_html(Path(args.htmldir)
                             if args.htmldir else problem.basedir)
