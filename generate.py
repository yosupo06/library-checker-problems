#!/usr/bin/env python3

import argparse
import shutil
from pathlib import Path
from subprocess import run, call, check_call, check_output, TimeoutExpired, CalledProcessError, DEVNULL, PIPE, STDOUT
from datetime import datetime
import toml
from tempfile import TemporaryDirectory

from os import getenv
from logging import Logger, basicConfig, getLogger

logger: Logger = getLogger(__name__)

def casename(name: str, i: int) -> str:
    # (random, 1) -> random_01
    return Path(name).stem + '_' + str(i).zfill(2)


class UnknownTypeFile(Exception):
    def __init__(self, message):
        super().__init__()
        self.message = message


def compile(src: Path, libdir: Path):
    if src.suffix == '.cpp':
        cxx = getenv('CXX', 'g++')
        cxxflags = getenv('CXXFLAGS', '-O2 -std=c++14 -Wall -Wextra').split()
        cxxflags.extend(['-I', libdir / 'common'])
        check_call([cxx] + cxxflags + ['-o', src.with_suffix('')] + [src])
    elif src.suffix == '.in':
        pass
    else:
        logger.error('Unknown type of file {}'.format(src))
        raise UnknownTypeFile('Unknown file: {}'.format(src))


def execcmd(src: Path, arg: [str] = []) -> [str]:
    # main.cpp -> ['main']
    # example.in -> ['cat', 'example_00.in']
    if src.suffix == '.cpp':
        cmd = [src.with_suffix('').resolve()]
        cmd.extend(arg)
        return cmd
    elif src.suffix == '.in':
        inpath = src.with_name(casename(src, int(arg[0])) + '.in')
        cmd = ['cat', inpath]
        return cmd
    else:
        raise UnknownTypeFile('Unknown file: {} {}'.format(src, arg))


class Problem:
    libdir: Path()
    basedir: Path()
    config = None

    def __init__(self, libdir: Path, basedir: Path):
        self.libdir = libdir
        self.basedir = basedir
        self.config = toml.load(basedir / 'info.toml')

    def compile(self):
        logger.info('compile files')

        logger.info('compile solution')
        compile(self.basedir / 'sol' / self.config['solution'], self.libdir)
        logger.info('compile checker')
        compile(self.basedir / 'checker.cpp', self.libdir)

        logger.info('compile verify')
        compile(self.basedir / 'gen' / self.config['verify'], self.libdir)

        logger.info('compile generators')
        for test in self.config['tests']:
            name = test['name']
            logger.info('compile {}'.format(name))
            compile(self.basedir / 'gen' / name, self.libdir)

        logger.info('compile (default) solutions')
        for test in self.config['tests']:
            name = test['name']
            logger.info('compile {}'.format(name))
            compile(self.basedir / 'gen' / name, self.libdir)

        for sol in self.config.get('solutions', []):
            name = sol['name']
            compile(self.basedir / 'sol' / name, self.libdir)


    def make_inputs(self):
        indir = self.basedir / 'in'
        gendir = self.basedir / 'gen'

        logger.info('clear input {}'.format(indir))
        if indir.exists():
            shutil.rmtree(indir)
        indir.mkdir()

#        logger.info('compile verify')
#        compile(gendir / self.config['verify'], self.libdir)

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            logger.info('case {} {}cases'.format(name, num))
#            logger.info('compile')
#            compile(gendir / name, self.libdir)

            for i in range(num):
                # output filename
                inpath = indir / (casename(name, i) + '.in')
                check_call(
                    execcmd(gendir / name, [str(i)]), stdout=open(inpath, 'w'))
                check_call(
                    execcmd(gendir / self.config['verify']), stdin=open(inpath, 'r'))

    def make_outputs(self):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        soldir = self.basedir / 'sol'

        logger.info('clear output {}'.format(outdir))
        if outdir.exists():
            shutil.rmtree(outdir)
        outdir.mkdir()

#        logger.info('compile sol')
#        compile(soldir / self.config['solution'], self.libdir)
#        checker = self.basedir / 'checker.cpp'
#        compile(checker, self.libdir)

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                outpath = outdir / (casename(name, i) + '.out')
                logger.info('start ' + casename(name, i) + '...')
                check_call(execcmd(soldir / self.config['solution']),
                           stdin=open(inpath, 'r'), stdout=open(outpath, 'w'))

    def judge(self, src: Path, config: dict):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        _tmpdir = TemporaryDirectory()
        tmpdir = _tmpdir.name
#        logger.info('compile source {} dir = {}'.format(src, tmpdir))
#        compile(src, self.libdir)
        checker = self.basedir / 'checker.cpp'
#        logger.info('compile checker')
#        compile(checker, self.libdir)
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
                checker_output = ''
                try:
                    check_call(execcmd(src), stdin=open(infile, 'r'), stdout=open(
                        actual, 'w'), timeout=self.config['timelimit'])
                except TimeoutExpired:
                    result = 'TLE'
                except CalledProcessError:
                    result = 'RE'
                else:
                    process = run(
                        execcmd(checker, [infile, actual, expected]), stdout=PIPE, stderr=STDOUT)
                    checker_output = process.stdout
                    if process.returncode:
                        result = 'WA'
                    else:
                        result = 'AC'
                end = datetime.now()

                results.add(result)
                usemsec = (end - start).seconds*1000 + \
                    (end - start).microseconds // 1000
                logger.info('{:>3s} {:6d} msecs : {} : {}'.format(
                    result, usemsec, case, checker_output))
        
        expectaccept = not config.get('wrong', False)
        actualaccept = (results == {'AC'})
        if expectaccept != actualaccept:
            logger.error('Fail {} : expect_accept = {} : results = {}'.format(src, expectaccept, results))
            exit(1)


if __name__ == '__main__':
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('toml', type=argparse.FileType('r'), help='Toml File')
    parser.add_argument('-p', '--problem', nargs='*', help='Generate problem', default=[])
    parser.add_argument('-s', '--solution', nargs='*', help='Solution Toml', default=[])
    parser.add_argument('--compileonly', action='store_true', help='Compile Test')
    args = parser.parse_args()

    problems = toml.load(args.toml)
    libdir = Path(args.toml.name).parent
    targetprobs = set(args.problem)

    probs = dict()

    for name, probinfo in problems['problems'].items():
        if targetprobs and name not in targetprobs:
            continue

        problem = Problem(libdir, libdir / probinfo['dir'])

        probs[name] = problem

        logger.info('Start {}'.format(probinfo['dir']))

        problem.compile()

        if args.compileonly:
            continue

        problem.make_inputs()
        problem.make_outputs()

        for sol in problem.config.get('solutions', []):
            problem.judge(problem.basedir / 'sol' / sol['name'], sol)

    for solpath in args.solution:
        soldir = Path(solpath).parent
        for name, sols in toml.load(solpath)['solutions'].items():
            if name not in probs:
                continue
            problem = probs[name]
            for sol in sols:
                compile(soldir / sol['source'], problems.libdir)
                if args.compileonly:
                    continue
                results = problem.judge(soldir / sol['source'], sol)

