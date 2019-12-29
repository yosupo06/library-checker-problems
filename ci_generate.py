#!/usr/bin/env python3

import argparse
from os import getenv
from subprocess import check_call

import toml

if __name__ == '__main__':
    parser = argparse.ArgumentParser(description='Testcase Generator for Matrix build')
    parser.add_argument('toml', type=argparse.FileType('r'), help='Toml File')
    parser.add_argument('num', type=int, help='# of server')
    parser.add_argument('id', type=int, help='server ID(0 <= id < num)')
    args = parser.parse_args()

    problems = toml.load(args.toml)
    all_names = sorted(problems['problems'].keys())

    n = len(all_names)

    names = [all_names[i] for i in range(args.id, n, args.num)]

    check_call(['./generate.py', args.toml.name, '--verify', '--sol', '-p'] + names)
