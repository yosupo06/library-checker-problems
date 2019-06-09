#!/usr/bin/env python3

import hashlib
import os
import subprocess
import tempfile
import zipfile
from pathlib import Path

import markdown
import markdown.extensions
import psycopg2  # pip3 install psycopg2
import toml

problems = toml.load('problems.toml')

print('[*] deploy problem to SQL')

print('[*] generate case')
# generate case
subprocess.check_call(['./generate.py', 'problems.toml'])

print('[*] connect SQL')
# connect sql
hostname = os.environ.get('POSTGRE_HOST', '127.0.0.1')
port = int(os.environ.get('POSTGRE_PORT', '5432'))
user = os.environ.get('POSTGRE_USER', 'postgres')
password = os.environ.get('POSTGRE_PASS', 'passwd')


conn = psycopg2.connect(
    host=hostname,
    port=port,
    user=user,
    password=password,
    database='librarychecker'
)


for problem in problems['Problems']:
    probdir = Path(problem['Dir'])
    name = probdir.name
    title = problem['Title']

    print('[*] deploy {}'.format(name))
    with tempfile.NamedTemporaryFile(suffix='.zip') as tmp:
        with zipfile.ZipFile(tmp.name, 'w') as newzip:
            newzip.write(probdir / 'checker.cpp', arcname='checker.cpp')
            for f in sorted(probdir.glob('in/*.in')):
                print(f)
                newzip.write(f, arcname=f.relative_to(probdir))
            for f in sorted(probdir.glob('out/*.out')):
                print(f)
                newzip.write(f, arcname=f.relative_to(probdir))

        tmp.seek(0)

        data = tmp.read()
        m = hashlib.sha256()
        m.update(data)
        datahash = m.hexdigest()

        # convert task
        statement = ''
        with probdir / 'task.md' as f:
            statement = markdown.markdown(
                f.read(), extensions=['markdown.extensions.fenced_code'])

        with conn.cursor() as cursor:
            cursor.execute('''
                insert into problems (name, title, statement, testhash, testzip)
                values (%s, %s, %s, %s, %s)
                on conflict(name) do update
                set (title, statement, testhash, testzip)
                = (EXCLUDED.title, EXCLUDED.statement,
                   EXCLUDED.testhash, EXCLUDED.testzip) 
                ''', (name, title, statement, datahash, data))
        conn.commit()
conn.close()
