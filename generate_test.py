#!/usr/bin/env python3

import unittest
from logging import basicConfig, getLogger
from os import getenv
from subprocess import PIPE, run

logger = getLogger(__name__)

# test of deprecated feature
class TestProblemToml(unittest.TestCase):
    def test_success(self):
        proc = run(
            ['./generate.py', 'problems_test.toml', '-p', 'simple_aplusb', '--verify', '--html'])
        self.assertEqual(proc.returncode, 0)

class TestSuccess(unittest.TestCase):
    def test_success(self):
        proc = run(
            ['./generate.py', '-p', 'simple_aplusb', '--verify', '--html'])
        self.assertEqual(proc.returncode, 0)

    def test_success_info_toml(self):
        proc = run(
            ['./generate.py', 'test/simple_aplusb/info.toml', '--verify', '--html'])
        self.assertEqual(proc.returncode, 0)


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


class TestUnusedGen(unittest.TestCase):
    def test_unused_gen(self):
        proc = run(
            ['./generate.py', '-p', 'unused_gen'])
        self.assertNotEqual(proc.returncode, 0)

if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    unittest.main()
