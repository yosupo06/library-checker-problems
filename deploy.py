#!/usr/bin/env python3

import argparse
import hashlib
import re
import shutil
import subprocess
import tempfile
import zipfile
from datetime import datetime
from logging import Logger, basicConfig, getLogger
from os import environ, getenv, path
from pathlib import Path
from struct import pack
from subprocess import (DEVNULL, PIPE, STDOUT, CalledProcessError,
                        TimeoutExpired, call, check_call, check_output, run)
from tempfile import TemporaryDirectory

import markdown.extensions
import psycopg2
import toml
from markdown import Extension, markdown
from markdown.preprocessors import Preprocessor

from generate import Problem

logger: Logger = getLogger(__name__)

if __name__ == "__main__":
    basicConfig(
        level=getenv('LOG_LEVEL', 'DEBUG'),
        format="%(asctime)s %(levelname)s %(name)s : %(message)s"
    )
    parser = argparse.ArgumentParser(description='Testcase Deploy')
    args = parser.parse_args()

    problems = toml.load('problems.toml')
    libdir = Path.cwd()

    logger.info('connect to SQL')
    hostname = environ.get('POSTGRE_HOST', '127.0.0.1')
    port = int(environ.get('POSTGRE_PORT', '5432'))
    user = environ.get('POSTGRE_USER', 'postgres')
    password = environ.get('POSTGRE_PASS', 'passwd')

    conn = psycopg2.connect(
        host=hostname,
        port=port,
        user=user,
        password=password,
        database='librarychecker'
    )

    for name, probinfo in problems['problems'].items():
        title = probinfo['title']
        problem = Problem(libdir, libdir / probinfo['dir'])
        probdir = problem.basedir
        timelimit = problem.config['timelimit']

        with tempfile.NamedTemporaryFile(suffix='.zip') as tmp:
            m = hashlib.sha256()

            with zipfile.ZipFile(tmp.name, 'w') as newzip:
                def zip_write(filename, arcname):
                    newzip.write(filename, arcname)
                    m.update(pack('q', path.getsize(filename)))
                    with open(filename, 'rb') as f:
                        m.update(f.read())
                zip_write(probdir / 'checker.cpp', arcname='checker.cpp')
                for f in sorted(probdir.glob('in/*.in')):
                    zip_write(f, arcname=f.relative_to(probdir))
                for f in sorted(probdir.glob('out/*.out')):
                    zip_write(f, arcname=f.relative_to(probdir))

            tmp.seek(0)
            data = tmp.read()
            datahash = m.hexdigest()

            print('[*] deploy {} {}'.format(name, datahash))

            # convert task
            html = problem.gen_html()
            statement = html.statement

            with conn.cursor() as cursor:
                cursor.execute(
                    'select testhash from problems where name = %s', (name, ))
                prevhash = cursor.fetchone()
                prevhash = prevhash[0] if prevhash else None
                cursor.execute('''
                    insert into problems (name, title, statement, timelimit)
                    values (%s, %s, %s, %s)
                    on conflict(name) do update
                    set (title, statement, timelimit)
                    = (EXCLUDED.title, EXCLUDED.statement, EXCLUDED.timelimit)
                    ''', (name, title, statement, int(timelimit * 1000)))
                if prevhash != datahash:
                    print('[!] upload data {} -> {}'.format(prevhash, datahash))
                    cursor.execute('''
                        update problems set (testhash, testzip) = (%s, %s) where name = %s
                        ''', (datahash, data, name))

            conn.commit()
    conn.close()
