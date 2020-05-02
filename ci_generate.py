#!/usr/bin/env python3

import os
import argparse
from pathlib import Path
import toml
import generate

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Testcase Generator for Matrix build')
    parser.add_argument('--show-list', action='store_true', help='Show problem list')
    parser.add_argument('num', type=int, help='# of server')
    parser.add_argument('id', type=int, help='server ID(1 <= id <= num)')
    parser.add_argument('args', nargs=argparse.REMAINDER)
    args = parser.parse_args()

    tomls = list(filter(lambda p: not p.match('test/**/info.toml'),
                   Path('.').glob('**/info.toml')))
    tomls = sorted(tomls, key=lambda x: x.parent.name)

    tomls = [tomls[i] for i in range(args.id - 1, len(tomls), args.num)]

    if args.show_list:
        print('Server ID: {} / {}'.format(args.id, args.num))
        print('Problem List:')
        for x in tomls:
            print('  {} {}'.format(x, generate.Problem(Path.cwd(), x).problem_version()))
    else:
        generate.main(['--verify'] + list(map(str, tomls)) + args.args)
