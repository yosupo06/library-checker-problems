#!/usr/bin/env python3

import sys
import argparse
import os
import platform
import shutil
import hashlib
import json
from datetime import datetime
from logging import Logger, basicConfig, getLogger, INFO
from os import getenv
from pathlib import Path
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
                        TimeoutExpired, call, check_call, check_output, run)
from tempfile import TemporaryDirectory
from typing import Any, Iterator, List, MutableMapping, Union, Optional

from enum import Enum
import toml

from problem import Problem, find_problem_dir

logger: Logger = getLogger(__name__)

def main(args: List[str]):
    try:
        import colorlog
    except ImportError:
        basicConfig(
            format="%(asctime)s [%(levelname)s] %(message)s",
            datefmt="%H:%M:%S",
            level=getenv('LOG_LEVEL', 'INFO'),
        )
        logger.warn('Please install colorlog: pip3 install colorlog')
    else:
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
            level=getenv('LOG_LEVEL', 'INFO'),
            handlers=[handler]
        )

    parser = argparse.ArgumentParser(description='Testcase Generator')
    parser.add_argument('toml', nargs='*', help='Toml File')
    parser.add_argument('-p', '--problem', nargs='*',
                        help='Generate problem', default=[])
    
    parser.add_argument('--dev', action='store_true', help='Developer Mode')
    parser.add_argument('--test', action='store_true', help='CI Mode')
    parser.add_argument('--clean', action='store_true', help='Clean in/out')
    parser.add_argument('--compile-checker',
                        action='store_true', help='Deprecated: Compile Checker')

    opts = parser.parse_args(args)

    if opts.dev + opts.test + opts.clean >= 2:
        raise ValueError('at most one of --dev, --test, --clean can be used')

    if opts.compile_checker:
        logger.warning(
            '--compile-checker is deprecated. Checker is compiled in default')

    rootdir: Path = Path(__file__).parent
    problems: List[Problem] = list()

    for tomlpath in opts.toml:
        problems.append(Problem(rootdir, Path(tomlpath).parent))

    for problem_name in opts.problem:
        problem_dir = find_problem_dir(rootdir, problem_name)
        if problem_dir is None:
            raise ValueError('Cannot find problem: {}'.format(problem_name))
        problems.append(Problem(rootdir, problem_dir))

    if len(problems) == 0:
        logger.warning('No problems')
    
    # suppress the annoying dialog appears when an application crashes on Windows
    if platform.uname().system == 'Windows':
        import ctypes 
        SEM_NOGPFAULTERRORBOX = 2 # https://msdn.microsoft.com/en-us/library/windows/desktop/ms684863(v=vs.85).aspx
        ctypes.windll.kernel32.SetErrorMode(SEM_NOGPFAULTERRORBOX)

    mode = Problem.Mode.DEFAULT
    if opts.dev:
        mode = Problem.Mode.DEV
    if opts.test:
        mode = Problem.Mode.TEST
    if opts.clean:
        mode = Problem.Mode.CLEAN

    for problem in problems:
        problem.generate(mode)

if __name__ == '__main__':
    main(sys.argv[1:])
