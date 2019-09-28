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
import toml
from markdown import Extension, markdown
from markdown.preprocessors import Preprocessor

logger: Logger = getLogger(__name__)


class ExampreExpander(Preprocessor):
    base_path = ''
    sample_template = '''
<div class="uk-grid-small uk-child-width-1-2@s" uk-grid>
    <div><pre>{}</pre></div>
    <div><pre>{}</pre></div>
</div>
'''

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

                infile = open(self.base_path / 'in' /
                              (name + '.in'), 'r').read()
                outfile = open(self.base_path / 'out' /
                               (name + '.out'), 'r').read()

                new_lines.append(r'### # {}'.format(counter))
                new_lines.extend(self.sample_template.format(
                    infile, outfile).splitlines())

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
        md.preprocessors.register(ExampreExpander(
            self.config['base_path']), 'example', 100)


class ToHTMLConverter:
    header = '''
<!DOCTYPE html>
<html lang="ja">
<head>
    <meta charset="UTF-8">

    <!-- Uikit -->
    <meta name="viewport" content="width=device-width, initial-scale=1">
    <link rel="stylesheet" href="https://judge.yosupo.jp/public/css/uikit.min.css" />
    <script src="https://judge.yosupo.jp/public/js/uikit.min.js"></script>
    <script src="https://judge.yosupo.jp/public/js/uikit-icons.min.js"></script>

    <!-- Katex -->
    <link rel="stylesheet" href="https://cdn.jsdelivr.net/npm/katex@0.10.2/dist/katex.min.css"
        integrity="sha384-yFRtMMDnQtDRO8rLpMIKrtPCD5jdktao2TV19YiZYWMDkUR5GQZR/NOVTdquEx1j" crossorigin="anonymous">
    <script defer src="https://cdn.jsdelivr.net/npm/katex@0.10.2/dist/katex.min.js"
        integrity="sha384-9Nhn55MVVN0/4OFx7EE5kpFBPsEMZxKTCnA+4fqDmg12eCTqGi6+BB2LjY8brQxJ"
        crossorigin="anonymous"></script>
    <script defer src="https://cdn.jsdelivr.net/npm/katex@0.10.2/dist/contrib/auto-render.min.js"
        integrity="sha384-kWPLUVMOks5AQFrykwIup5lo0m3iMkkHrD0uJ4H5cjeGihAutqP0yW0J6dpFiVkI" crossorigin="anonymous"
        onload="renderMathInElement(document.body);"></script>
    <script>// <![CDATA[
        document.addEventListener("DOMContentLoaded", function () {
            renderMathInElement(
                document.body, {
                    delimiters: [
                        { left: "$$", right: "$$", display: true },
                        { left: "$", right: "$", display: false }],
                    ignoredTags: [],
                })
        });
    // ]]></script>
</head>
'''
    body_template = '''
<body>
    <section class="uk-section">
        <div class="uk-container">
            {}
        </div>
    </section>
</body>
</html>
'''
    html: str
    statement: str

    def __init__(self, probdir: Path):
        with open(probdir / 'task.md', encoding='utf-8') as f:
            self.statement = markdown(
                f.read(), extensions=[
                    'markdown.extensions.fenced_code',
                    'markdown.extensions.tables',
                    ExampleExtension(base_path=str(probdir))
                ],
            )
            self.html = self.header + self.body_template.format(self.statement)
