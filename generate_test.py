#!/usr/bin/env python3

import unittest
from logging import basicConfig, getLogger
from os import chdir, getenv
from subprocess import PIPE, run
from pathlib import Path
from generate import Problem
from typing import List
logger = getLogger(__name__)

# test of deprecated feature


class TestSuccess(unittest.TestCase):
    def test_success(self):
        proc = run(
            ['./generate.py', '-p', 'simple_aplusb', '--verify', '--html'])
        self.assertEqual(proc.returncode, 0)

    def test_success_info_toml(self):
        proc = run(
            ['./generate.py', 'test/simple_aplusb/info.toml', '--verify', '--html'])
        self.assertEqual(proc.returncode, 0)


# warn: --compile-checker is used in other project(e.g. kmyk/online-judge-verify-helper)
class TestCompileChecker(unittest.TestCase):
    def test_compile_checker(self):
        checker = Path('test/simple_aplusb/checker')
        if checker.exists():
            checker.unlink()
        proc = run(
            ['./generate.py', '-p', 'simple_aplusb', '--compile-checker'])
        self.assertEqual(proc.returncode, 0)
        self.assertTrue(checker.exists())


class TestVerify(unittest.TestCase):
    def test_no_verify(self):
        proc = run(
            ['./generate.py', '-p', 'failed_verify'])
        self.assertEqual(proc.returncode, 0)

    def test_failed_verify(self):
        proc = run(['./generate.py', '-p', 'failed_verify', '--verify'])
        self.assertNotEqual(proc.returncode, 0)


class TestNonExistProblem(unittest.TestCase):
    def test_non_exist_problem(self):
        proc = run(
            ['./generate.py', '-p', 'dummy_problem'])
        self.assertNotEqual(proc.returncode, 0)


class TestUnusedExample(unittest.TestCase):
    def test_no_html(self):
        proc = run(
            ['./generate.py', '-p', 'unused_example'])
        self.assertEqual(proc.returncode, 0)

    def test_unused_example(self):
        proc = run(
            ['./generate.py', '-p', 'unused_example', '--html'])
        self.assertNotEqual(proc.returncode, 0)


class TestNonExistdExample(unittest.TestCase):
    def test_no_html(self):
        proc = run(
            ['./generate.py', '-p', 'nonexist_example'])
        self.assertEqual(proc.returncode, 0)

    def test_unused_example(self):
        proc = run(
            ['./generate.py', '-p', 'nonexist_example', '--html'])
        self.assertNotEqual(proc.returncode, 0)


class TestUnusedGen(unittest.TestCase):
    def test_unused_gen(self):
        proc = run(
            ['./generate.py', '-p', 'unused_gen'])
        self.assertNotEqual(proc.returncode, 0)


class TestNoTitle(unittest.TestCase):
    def test_no_title(self):
        proc = run(
            ['./generate.py', '-p', 'no_title'])
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
        proc = run(
            ['./generate.py', '-p', 'allow_tle', '--verify'])
        self.assertEqual(proc.returncode, 0)


class TestOtherCheckerPlace(unittest.TestCase):
    def test_other_checker_place(self):
        proc = run(
            ['./generate.py', '-p', 'other_checker_place'])
        self.assertEqual(proc.returncode, 0)


class TestOtherVerifierPlace(unittest.TestCase):
    def test_other_verifier_place(self):
        proc = run(
            ['./generate.py', '-p', 'other_verifier_place'])
        self.assertEqual(proc.returncode, 0)


class TestListDependingFiles(unittest.TestCase):
    def test_list_depending_files(self):
        problem = Problem(Path.cwd(), Path('sample/aplusb'))
        files = list(problem.list_depending_files()) # type: List[Path]
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
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    unittest.main()
