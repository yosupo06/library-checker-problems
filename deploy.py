#!/usr/bin/env python3

import hashlib
from os import environ
import subprocess
import tempfile
import zipfile
from pathlib import Path

from markdown import markdown, Extension
import markdown.extensions
from markdown.preprocessors import Preprocessor

import psycopg2  # pip3 install psycopg2
import toml

import re

class ExampreExpander(Preprocessor):
    base_path = ''
    def __init__(self, base_path):
        self.base_path = Path(base_path[0])

    def run(self, lines):        
        new_lines = []
        counter = 1
        for line in lines:
            start = '{{example '
            end = '}}'
            if line.startswith(start) and line.endswith(end):
                name = line[len(start):-len(end)]

                infile = open(self.base_path / 'in' / (name + '.in'), 'r').read()
                outfile = open(self.base_path / 'out' / (name + '.out'), 'r').read()
                
                new_lines.append('\# {}'.format(counter))
                new_lines.append('------')

            
                new_lines.extend('''
<div class="uk-grid-small uk-child-width-1-2@s" uk-grid>
    <div><pre>{}</pre></div>
    <div><pre>{}</pre></div>
</div>
                '''.format(infile, outfile).splitlines())

                counter += 1
            else:
                new_lines.append(line)
        return new_lines

class ExampleExtension(Extension):
    def __init__(self, **kwargs):        
        self.config = {
            'base_path': ['.', 'Base path']
        }
        super(ExampleExtension, self).__init__(**kwargs)

    def extendMarkdown(self, md):
        md.preprocessors.register(ExampreExpander(self.config['base_path']), 'example', 100)

problems = toml.load('problems.toml')

print('[*] deploy problem to SQL')

print('[*] connect SQL')
# connect sql
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


for problem in problems['problems']:
    probdir = Path(problem['dir'])
    name = probdir.name
    title = problem['title']

    print('[*] deploy {}'.format(name))
    with tempfile.NamedTemporaryFile(suffix='.zip') as tmp:
        with zipfile.ZipFile(tmp.name, 'w') as newzip:
            newzip.write(probdir / 'checker.cpp', arcname='checker.cpp')
            for f in sorted(probdir.glob('in/*.in')):
                newzip.write(f, arcname=f.relative_to(probdir))
            for f in sorted(probdir.glob('out/*.out')):
                newzip.write(f, arcname=f.relative_to(probdir))

        tmp.seek(0)

        data = tmp.read()
        m = hashlib.sha256()
        m.update(data)
        datahash = m.hexdigest()

        # convert task
        statement = ''
        with open(probdir / 'task.md') as f:
            statement = markdown.markdown(
                f.read(), extensions=[
                    'markdown.extensions.fenced_code',
                    'markdown.extensions.tables',
                    ExampleExtension(base_path = str(probdir))
                ],
            )

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
