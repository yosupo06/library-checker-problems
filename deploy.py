#!/usr/bin/env python3

import os, toml, glob
import tempfile, zipfile
import hashlib
import subprocess
import markdown
import markdown.extensions
import psycopg2 #pip3 install psycopg2


print('[*] deploy problem to SQL')

print('[*] generate case')
# generate case
tomlpath = os.path.abspath('./problems.toml')
tomldir = os.path.dirname(tomlpath)
subprocess.check_call(['./generate.py', tomlpath])
problems = toml.load(tomlpath)

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
    probdir = os.path.join(tomldir, problem['Dir'])
    _, name = os.path.split(probdir)
    print('[*] deploy {}'.format(name))
    with tempfile.NamedTemporaryFile(suffix='.zip') as tmp:
        with zipfile.ZipFile(tmp.name, 'w') as newzip:
            for f in sorted(glob.glob(probdir + '/in/*.in')):
                print(f, ' ', os.path.relpath(f, probdir))
                newzip.write(f, arcname=os.path.relpath(f, probdir))
            for f in sorted(glob.glob(probdir + '/out/*.out')):
                print(f, ' ', os.path.relpath(f, probdir))
                newzip.write(f, arcname=os.path.relpath(f, probdir))

        tmp.seek(0)

        data = tmp.read()
        m = hashlib.sha256()
        m.update(data)
        datahash = m.hexdigest()

        # convert task
        statement = ''
        with open(os.path.join(probdir, 'task.md')) as f:
            statement = markdown.markdown(f.read(), extensions = ['markdown.extensions.fenced_code'])

        with conn.cursor() as cursor:
            cursor.execute('''
                insert into problems (name, statement, testhash, testzip) values (%s, %s, %s, %s)
                on conflict(name) do update
                set (statement, testhash, testzip)
                = (EXCLUDED.statement, EXCLUDED.testhash, EXCLUDED.testzip) 
                ''',
                (name, statement, datahash, data))
        conn.commit()
conn.close()

# upload problems
