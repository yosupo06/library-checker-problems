#!/usr/bin/env python3

import unittest
import json
import colorlog
from logging import basicConfig, getLogger
from os import chdir, getenv
from subprocess import run, check_output
from shutil import copy
from pathlib import Path
from tempfile import TemporaryDirectory
from problem import Problem
from typing import List
logger = getLogger(__name__)

@unittest.skipIf(getenv('ENABLE_GENERATE_TEST') == None)
class TestGenerateAll(unittest.TestCase):
    def test_generate_all(self):
        tomls = list(filter(lambda p: not p.match('test/**/info.toml'), Path('.').glob('**/info.toml')))
        tomls = sorted(tomls, key=lambda x: x.parent.name)

        cache_path = Path(getenv('VERSIONS_CACHE_PATH'))
        versions = json.load(open(cache_path, 'r')) if cache_path.exists() else dict()

        for toml in tomls:
            problem = Problem(Path.cwd(), toml.parent)
            name = problem.basedir.name
            version = problem.problem_version()

            with self.subTest(name=name):
                if versions.get(name) == version:
                    logger.info('Skip generated problem: {}'.format(name))
                else:
                    logger.info('Generate {}'.format(name))
                    problem.generate(mode=Problem.Mode.TEST)
                    problem.generate(mode=Problem.Mode.CLEAN)
                    versions[name] = version

        with open(cache_path, 'w') as f:
            json.dump(versions, f)
        


def create_test_dir(problem_name: str) -> TemporaryDirectory:
    problem_dir = Path('test') / problem_name
    files = check_output(
        ['git', 'ls-files', str(problem_dir)]).decode('utf-8').split()
    new_dir = TemporaryDirectory()
    for f in files:
        path = Path(f).relative_to(Path('test'))
        src = Path('test') / path  # type: Path
        trg = Path(new_dir.name) / path  # type: Path
        if not trg.parent.exists():
            trg.parent.mkdir(parents=True)
        copy(str(src), str(trg))
    return new_dir


class TestSuccess(unittest.TestCase):
    # select problem by problem id
    def test_success_user(self):
        with create_test_dir('simple_aplusb') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml')])
            self.assertEqual(proc.returncode, 0)

    def test_success_dev(self):
        with create_test_dir('simple_aplusb') as test_dir:
            proc = run(['./generate.py', str(Path(test_dir) /
                       'simple_aplusb/info.toml'), '--dev'])
            self.assertEqual(proc.returncode, 0)

    def test_success_test(self):
        with create_test_dir('simple_aplusb') as test_dir:
            proc = run(['./generate.py', str(Path(test_dir) /
                       'simple_aplusb/info.toml'), '--test'])
            self.assertEqual(proc.returncode, 0)


class TestClean(unittest.TestCase):
    # select problem by problem id
    def test_clean(self):
        with create_test_dir('simple_aplusb') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml')])
            self.assertEqual(proc.returncode, 0)
            self.assertTrue((Path(test_dir) / 'simple_aplusb' / 'in').exists())
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml'), '--clean'])
            self.assertEqual(proc.returncode, 0)
            self.assertFalse(
                (Path(test_dir) / 'simple_aplusb' / 'in').exists())
            # it is ok to run twice
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml'), '--clean'])
            self.assertEqual(proc.returncode, 0)

# warn: --compile-checker is used in other project(e.g. kmyk/online-judge-verify-helper)


class TestCompileChecker(unittest.TestCase):
    def test_compile_checker(self):
        with create_test_dir('simple_aplusb') as test_dir:
            checker = Path(test_dir) / 'simple_aplusb/checker'
            self.assertFalse(checker.exists())
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml'), '--compile-checker'])
            self.assertEqual(proc.returncode, 0)
            self.assertTrue(checker.exists())

    def test_compile_checker_nocopy(self):
        checker = Path('test/simple_aplusb/checker')
        if checker.exists():
            checker.unlink()
        proc = run(
            ['./generate.py', '-p', 'simple_aplusb', '--compile-checker'])
        self.assertEqual(proc.returncode, 0)
        self.assertTrue(checker.exists())


class TestVerify(unittest.TestCase):
    def test_no_verify_user(self):
        with create_test_dir('failed_verify') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'failed_verify/info.toml')])
            self.assertEqual(proc.returncode, 0)

    def test_no_verify_dev(self):
        with create_test_dir('failed_verify') as test_dir:
            proc = run(['./generate.py', str(Path(test_dir) /
                       'failed_verify/info.toml'), '--dev'])
            self.assertNotEqual(proc.returncode, 0)

    def test_no_verify_test(self):
        with create_test_dir('failed_verify') as test_dir:
            proc = run(['./generate.py', str(Path(test_dir) /
                       'failed_verify/info.toml'), '--test'])
            self.assertNotEqual(proc.returncode, 0)


class TestNonExistProblem(unittest.TestCase):
    def test_non_exist_problem(self):
        proc = run(
            ['./generate.py', '-p', 'dummy_problem'])
        self.assertNotEqual(proc.returncode, 0)

class TestUnusedGen(unittest.TestCase):
    def test_unused_gen_user(self):
        with create_test_dir('unused_gen') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'unused_gen/info.toml')])
            self.assertNotEqual(proc.returncode, 0)

    def test_unused_gen_dev(self):
        with create_test_dir('unused_gen') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'unused_gen/info.toml'), '--dev'])
            self.assertEqual(proc.returncode, 0)

    def test_unused_gen_test(self):
        with create_test_dir('unused_gen') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'unused_gen/info.toml'), '--test'])
            self.assertNotEqual(proc.returncode, 0)


class TestNoTitle(unittest.TestCase):
    def test_no_title_user(self):
        with create_test_dir('no_title') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'no_title/info.toml')])
            self.assertNotEqual(proc.returncode, 0)

    def test_no_title_dev(self):
        with create_test_dir('no_title') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'no_title/info.toml'), '--dev'])
            self.assertEqual(proc.returncode, 0)

    def test_no_title_test(self):
        with create_test_dir('no_title') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'no_title/info.toml'), '--test'])
            self.assertNotEqual(proc.returncode, 0)


class TestCallFromOutside(unittest.TestCase):
    def test_call_from_outside(self):
        cwd = Path.cwd()
        try:
            chdir('/')
            proc = run(
                [str(cwd / 'generate.py'), str(cwd / 'test/simple_aplusb/info.toml')])
            self.assertEqual(proc.returncode, 0)
        finally:
            chdir(str(cwd))


class TestAllowTLE(unittest.TestCase):
    def test_allow_tle(self):
        with create_test_dir('allow_tle') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'allow_tle/info.toml'), '--test'])
            self.assertEqual(proc.returncode, 0)


class TestOtherCheckerPlace(unittest.TestCase):
    def test_other_checker_place(self):
        with create_test_dir('other_checker_place') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'other_checker_place/info.toml'), '--test'])
            self.assertEqual(proc.returncode, 0)


class TestOtherVerifierPlace(unittest.TestCase):
    def test_other_verifier_place(self):
        with create_test_dir('other_verifier_place') as test_dir:
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'other_verifier_place/info.toml'), '--test'])
            self.assertEqual(proc.returncode, 0)


class TestCacheTest(unittest.TestCase):
    def test_cache_user(self):
        with create_test_dir('simple_aplusb') as test_dir:
            in_path = Path(test_dir) / \
                'simple_aplusb/in/random_00.in'  # type: Path
            self.assertFalse(in_path.exists())
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml')])
            self.assertTrue(in_path.exists())
            time = in_path.stat().st_mtime_ns
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml')])
            self.assertTrue(in_path.exists())
            self.assertEqual(time, in_path.stat().st_mtime_ns)

    def test_cache_dev(self):
        with create_test_dir('simple_aplusb') as test_dir:
            in_path = Path(test_dir) / \
                'simple_aplusb/in/random_00.in'  # type: Path
            self.assertFalse(in_path.exists())
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml'), '--dev'])
            self.assertTrue(in_path.exists())
            time = in_path.stat().st_mtime_ns
            proc = run(
                ['./generate.py', str(Path(test_dir) / 'simple_aplusb/info.toml'), '--dev'])
            self.assertTrue(in_path.exists())
            self.assertNotEqual(time, in_path.stat().st_mtime_ns)


class TestListDependingFiles(unittest.TestCase):
    def test_list_depending_files(self):
        problem = Problem(Path.cwd(), Path('sample/aplusb'))
        files = list(problem.list_depending_files())  # type: List[Path]
        find_random = False
        find_verifier = False
        for f in files:
            if f.resolve() == Path('common/random.h').resolve():
                find_random = True
            if f.resolve() == Path('sample/aplusb/verifier.cpp').resolve():
                find_verifier = True
        self.assertTrue(find_random)
        self.assertTrue(find_verifier)

if __name__ == "__main__":
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
        level=getenv('LOG_LEVEL', 'DEBUG'),
        handlers=[handler]
    )

    unittest.main()
