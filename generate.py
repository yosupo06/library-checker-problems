#!/usr/bin/env python3

import argparse
import shutil
from pathlib import Path
from subprocess import run, call, check_call, check_output, TimeoutExpired, CalledProcessError, DEVNULL, PIPE, STDOUT
from datetime import datetime
import toml
from tempfile import TemporaryDirectory

def casename(name: str, i: int) -> str:
    # (random, 1) -> random_01
    return Path(name).stem + '_' + str(i).zfill(2)


class UnknownTypeFile(Exception):
    def __init__(self, message):
        super().__init__()
        self.message = message


def compile(src: Path, libdir: Path):
    if src.suffix == '.cpp':
        check_call(['g++', '-O2', '-std=c++14',
                    '-I', libdir / 'common',
                    '-o', src.with_suffix(''),
                    src])
    elif src.suffix == '.in':
        pass
    else:
        print('Unknown type of file {}'.format(src))
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

    def make_inputs(self):
        indir = self.basedir / 'in'
        gendir = self.basedir / 'gen'

        print('[#] clear input {}'.format(indir))
        if indir.exists():
            shutil.rmtree(indir)
        indir.mkdir()

        print('[#] compile verify')
        compile(gendir / self.config['verify'], self.libdir)

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            print('[#] case {} {}cases'.format(name, num))
            print('[#] compile')
            compile(gendir / name, self.libdir)

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

        print('[#] clear output {}'.format(outdir))
        if outdir.exists():
            shutil.rmtree(outdir)
        outdir.mkdir()

        print('[#] compile sol')
        compile(soldir / self.config['solution'], self.libdir)

        for test in self.config['tests']:
            name = test['name']
            num = test['number']

            for i in range(num):
                inpath = indir / (casename(name, i) + '.in')
                outpath = outdir / (casename(name, i) + '.out')
                print('# start ' + casename(name, i) + '...')
                check_call(execcmd(soldir / self.config['solution']),
                           stdin=open(inpath, 'r'), stdout=open(outpath, 'w'))

    def judge(self, src: Path, config: dict):
        indir = self.basedir / 'in'
        outdir = self.basedir / 'out'
        _tmpdir = TemporaryDirectory()
        tmpdir = _tmpdir.name
        print('[#] compile source {} dir = {}'.format(src, tmpdir))
        compile(src, self.libdir)
        checker = self.basedir / 'checker.cpp'
        print('[#] compile checker')
        compile(checker, self.libdir)
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
                print('{:>3s} {:6d} msecs : {} : {}'.format(
                    result, usemsec, case, checker_output))
        
        expectaccept = not config.get('wrong', False)
        actualaccept = (results == {'AC'})
        if expectaccept != actualaccept:
            print("Fail {} : expect_accept = {} : results = {}".format(src, expectaccept, results))
            exit(1)


if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('toml', type=argparse.FileType('r'), help='Toml File')
    parser.add_argument('-p', '--problem', nargs='*', help='Generate problem', default=[])
    parser.add_argument('-s', '--solution', nargs='*', help='Solution Toml', default=[])
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

        print('[*] Start {}'.format(probinfo['dir']))

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
                results = problem.judge(soldir / sol['source'], sol)

