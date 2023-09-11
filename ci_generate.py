#!/usr/bin/env python3

import os
import argparse
from pathlib import Path
import toml
import generate
from problem import Problem
import json
from logging import Logger, basicConfig, getLogger
from os import getenv
from typing import Dict

logger = getLogger(__name__)  # type: Logger

def main():
    parser = argparse.ArgumentParser(
        description='Testcase generator')
    parser.add_argument('--print-version', action='store_true', help='Print version')
    args = parser.parse_args()

    basicConfig(
        level=getenv('LOG_LEVEL', 'INFO'),
        format="%(asctime)s [%(levelname)s] %(message)s"
    )

    tomls = list(filter(lambda p: not p.match('test/**/info.toml'),
                        Path('.').glob('**/info.toml')))
    tomls = sorted(tomls, key=lambda x: x.parent.name)

    versions = dict() # type: Dict[str, str]
    for x in tomls:
        problem = generate.Problem(Path.cwd(), x.parent)
        problem_name = problem.basedir.name
        problem_version = problem.problem_version()
        versions[problem_name] = problem_version

    if args.print_version:
        print(json.dumps(versions))
        return

    cache_dir = Path('cache')
    if not cache_dir.exists():
        cache_dir.mkdir()

    cache = cache_dir / 'generated.json'
    generated = json.load(open(str(cache))) if cache.exists() else dict()

    for x in tomls:
        problem = Problem(Path.cwd(), x.parent)
        problem_name = problem.basedir.name
        problem_version = problem.problem_version()
        if problem_name in generated and generated[problem_name] == problem_version:
            logger.info('Problem {} is already generated, skip'.format(problem_name))
        else:
            logger.info('Generate {}, new version: {}'.format(problem_name, problem_version))
            problem.generate(mode=Problem.Mode.TEST)
            problem.generate(mode=Problem.Mode.CLEAN)
        if problem_name not in generated:
            generated[problem_name] = dict()

    with open(str(cache), 'w') as f:
        json.dump(versions, f)

if __name__ == '__main__':
    main()
