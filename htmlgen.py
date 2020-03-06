#!/usr/bin/env python3

import argparse
import hashlib
import re
import math
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

logger = getLogger(__name__)  # type: Logger


class ParamsExpander(Preprocessor):
    def __init__(self, params):
        self.params = params

        self.patterns = []
        for key, value in self.params[0].items():
            a = re.compile(r'{{{{\s*param\s+{}\s*}}}}'.format(key))
            if isinstance(value, int):
                if str(value).endswith('000000'):
                    k = math.floor(math.log10(value))
                    if value == 10 ** k:
                        b = r'10^{{{}}}'.format(k)
                    else:
                        b = r'{} \\times 10^{{{}}}'.format(value / 10 ** k, k)
                else:
                    b = format(value, ',').replace(',', '{,}')
            else:
                b = str(value)
            self.patterns.append((a, b))
        self.failure = re.compile(r'{{\s*param\s+\w+\s*}}')

    def run(self, lines):
        new_lines = []
        for line in lines:
            for a, b in self.patterns:
                line = re.sub(a, b, line)
            m = re.search(self.failure, line)
            if m:
                logger.error('The template {} is not replaced'.format(repr(m.group(0))))
                exit(1)
            new_lines.append(line)
        return new_lines


class ParamsExtension(Extension):
    def __init__(self, **kwargs):
        self.config = {
            'params': [{}, 'Parameters'],
        }
        super(ParamsExtension, self).__init__(**kwargs)

    def extendMarkdown(self, md):
        md.preprocessors.register(ParamsExpander(
            self.config['params']), 'params', 99)


class ExampleExpander(Preprocessor):
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
        used_examples = []
        new_lines = []
        counter = 1
        for line in lines:
            start = '{{example '
            end = '}}'
            if line.startswith(start) and line.endswith(end):
                name = line[len(start):-len(end)]
                inpath = self.base_path / 'in' / (name + '.in')
                if not inpath.exists():
                    logger.error('task require non exist file: {}'.format(inpath))
                    exit(1)
                inpath = str(inpath)
                used_examples.append(inpath)

                infile = open(inpath).read()
                outfile = open(str(self.base_path / 'out' /
                                   (name + '.out')), 'r').read()

                new_lines.append(r'### # {}'.format(counter))
                new_lines.extend(self.sample_template.format(
                    infile, outfile).splitlines())

                counter += 1
            else:
                new_lines.append(line)

        for name in Path(self.base_path).glob('in/example_*.in'):
            if str(name) not in used_examples:
                logger.error('Not use {} for task'.format(name))
                exit(1)

        return new_lines


class ExampleExtension(Extension):
    def __init__(self, **kwargs):
        self.config = {
            'base_path': ['.', 'Base path']
        }
        super(ExampleExtension, self).__init__(**kwargs)

    def extendMarkdown(self, md):
        md.preprocessors.register(ExampleExpander(
            self.config['base_path']), 'example', 100)


class ForumExpander(Preprocessor):
    forum_template = '''
<a class="uk-button uk-button-default" href={url}>Forum <span uk-icon="icon: link"></span></a>
'''

    def __init__(self, url):
        self.url = url[0]

    def run(self, lines):
        new_lines = []
        for line in lines:
            new_lines.append(line)
        if self.url:
            new_lines.append('')
            new_lines.append('---')
            new_lines.append('')
            new_lines.append(self.forum_template.format(url=self.url))
            new_lines.append('')
        return new_lines


class ForumExtension(Extension):
    def __init__(self, **kwargs):
        self.config = {
            'url': ['dummy issue URL', 'URL'],
        }
        super(ForumExtension, self).__init__(**kwargs)

    def extendMarkdown(self, md):
        md.preprocessors.register(ForumExpander(
            self.config['url']), 'forum', 101)


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

    def __init__(self, probdir: Path, config):
        with open(str(probdir / 'task.md'), encoding='utf-8') as f:
            self.statement = markdown(
                f.read(), extensions=[
                    'md_in_html',
                    'markdown.extensions.fenced_code',
                    'markdown.extensions.tables',
                    ParamsExtension(params=config.get('params', {})),
                    ExampleExtension(base_path=str(probdir)),
                    ForumExtension(url=config.get('forum', ''))
                ],
            )  # type: str
            self.html = self.header + \
                self.body_template.format(self.statement)  # type: str
