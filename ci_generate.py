#!/usr/bin/env python3

import os
import argparse
from pathlib import Path
import toml
import generate
import json


if __name__ == '__main__':
    parser = argparse.ArgumentParser(
        description='Testcase Generator for Matrix build')
    parser.add_argument('--html', action='store_true', help='Generate HTML')
    parser.add_argument('--htmldir', help='Generate HTML', default=None)
    args = parser.parse_args()

    tomls = list(filter(lambda p: not p.match('test/**/info.toml'),
                        Path('.').glob('**/info.toml')))
    tomls = sorted(tomls, key=lambda x: x.parent.name)

    cache = Path('generated.json')
    generated = json.load(open(cache)) if cache.exists() else dict()

    for x in tomls:
        problem = generate.Problem(Path.cwd(), x.parent)
        problem_name = problem.basedir.name
        problem_version = problem.problem_version()
        if problem_name in generated and problem_version in generated[problem_name]:
            print('Problem {} is already generated, skip'.format(problem_name))
        else:
            print('Generate {}'.format(problem_name))
            generate.generate(problem, force_generate=True, rewrite_hash=False,
                              verify=True, compile_checker=True, generate_html=args.html, html_dir=Path(args.htmldir) if args.htmldir else None)
        if problem_name not in generated:
            generated[problem_name] = dict()
        generated[problem_name][problem_version] = True
    with open('generated.json', 'w') as f:
        json.dump(generated, f)
