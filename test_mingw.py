#!/usr/bin/env python3

import os
import argparse
from pathlib import Path
import toml
import generate
import json
from logging import Logger, basicConfig, getLogger
from os import getenv
from typing import Dict

logger = getLogger(__name__)  # type: Logger

def main():
    parser = argparse.ArgumentParser(
        description='Testcase Generator for Matrix build')
    args = parser.parse_args()

    basicConfig(
        level=getenv('LOG_LEVEL', 'INFO'),
        format="%(asctime)s [%(levelname)s] %(message)s"
    )

    tomls = list(filter(lambda p: not p.match('test/**/info.toml'),
                        Path('.').glob('**/info.toml')))
    tomls = sorted(tomls, key=lambda x: x.parent.name)

    logger.info(Path.cwd())
    x = Path('sample/aplusb/info.toml')
    problem = generate.Problem(Path.cwd(), x.parent)
    problem_name = problem.basedir.name
    problem_version = problem.problem_version()
    logger.info(problem_name)
    logger.info(problem_version)
    logger.info(list(problem.list_depending_files()))

if __name__ == '__main__':
    main()
