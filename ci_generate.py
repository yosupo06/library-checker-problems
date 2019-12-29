#!/usr/bin/env python3

import argparse
from os import getenv
from subprocess import check_call

import toml

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Testcase Generator for Matrix build')
    parser.add_argument('--show-list', action='store_true', help='Show problem list')
    parser.add_argument('toml', type=argparse.FileType('r'), help='Toml File')
    parser.add_argument('num', type=int, help='# of server')
    parser.add_argument('id', type=int, help='server ID(1 <= id <= num)')
    parser.add_argument('args', nargs=argparse.REMAINDER)
    args = parser.parse_args()

    problems = toml.load(args.toml)
    all_names = sorted(problems['problems'].keys())
    print(args)
    n = len(all_names)

    names = [all_names[i] for i in range(args.id - 1, n, args.num)]

    if args.show_list:
        print('Server ID: {} / {}'.format(args.id, args.num))
        print('Problem List:')
        for n in names:
            print('  {}'.format(n))
    else:
        check_call(['./generate.py', args.toml.name, '--verify', '--sol', '-p'] + names + args.args)
