#!/usr/bin/env python3

import unittest
from logging import basicConfig, getLogger
from os import getenv
from problem import param_to_str

logger = getLogger(__name__)

class TestParam(unittest.TestCase):
    # select problem by problem id
    def test_convert_integer(self):
        self.assertEqual(param_to_str('A', 100), "#define A (long long)100")
        self.assertEqual(param_to_str('A', 1_000_000_007), "#define A (long long)1000000007")
        self.assertEqual(param_to_str('A', 998244353), "#define A (long long)998244353")

if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    unittest.main()
