#!/usr/bin/env python3

import argparse
import hashlib
import math
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
from jinja2 import Template, Environment, DictLoader
import toml
from markdown import Extension, markdown
from markdown.preprocessors import Preprocessor

from generate import Problem
from typing import Set

logger = getLogger(__name__)  # type: Logger


# html tag for change lang
def lang_div_start(lang):
    return '<div class="lang-{}">'.format(lang)


def lang_div_end(lang):
    return '</div>'


# {{keyword.statement}}, {{keyword.constraints}}, ...
def to_keyword_str(lang_dict):
    s = ''
    for k, v in lang_dict.items():
        s += lang_div_start(k) + v + lang_div_end(k)
    return s


keywords = {
    'statement': to_keyword_str({
        'en': 'Problem Statement',
        'ja': '問題文',
    }),
    'constraints': to_keyword_str({
        'en': 'Constraints',
        'ja': '制約',
    }),
    'input': to_keyword_str({
        'en': 'Input',
        'ja': '入力',
    }),
    'output': to_keyword_str({
        'en': 'Output',
        'ja': '出力',
    }),
    'sample': to_keyword_str({
        'en': 'Sample',
        'ja': 'サンプル',
    }),
}


def param_to_str(value):
    if isinstance(value, int):
        if str(value).endswith('000000'):
            k = math.floor(math.log10(value))
            if value == 10 ** k:
                return r'10^{{{}}}'.format(k)
            elif value % (10 ** k) == 0:
                return r'{} \\times 10^{{{}}}'.format(value // 10 ** k, k)
            else:
                return r'{} \\times 10^{{{}}}'.format(value / 10 ** k, k)
        else:
            return format(value, ',').replace(',', '{,}')
    else:
        return str(value)


def gen_params(toml_params):
    params = dict()  # type: Dict[str, str]
    for key, value in toml_params.items():
        params[key] = param_to_str(value)
    return params


# @{example.example_00}
class ExampleReader:
    sample_template = '''
<div class="uk-grid-small uk-child-width-1-2@s" uk-grid>
    <div><pre>{}</pre></div>
    <div><pre>{}</pre></div>
</div>
'''

    def __init__(self, problem_dir: Path):
        self.counter = 1
        self.problem_dir = problem_dir
        self.used = set()  # type: Set[str]

    def __getitem__(self, key: str):
        logger.debug('read example: {}'.format(key))
        self.used.add(key)
        inpath = self.problem_dir / 'in' / (key + '.in')
        outpath = self.problem_dir / 'out' / (key + '.out')
        infile = open(inpath, 'r').read()
        outfile = open(outpath, 'r').read()

        s = r'<h3># {}</h3>'.format(self.counter)
        self.counter += 1
        s += self.sample_template.format(infile, outfile)
        return s

# {{setlang('en')}}, {{resetlang()}}


class LangManager:
    def __init__(self):
        self.now_lang = ''

    def __getitem__(self, lang: str):
        if lang == 'end':
            return self.reset_lang()
        s = ''
        if self.now_lang != '':
            s += self.reset_lang()
        self.now_lang = lang
        return s + lang_div_start(lang)

    def reset_lang(self):
        s = lang_div_end(self.now_lang)
        self.now_lang = ''
        return s



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


html_header = '''
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
    <script>
        document.addEventListener("DOMContentLoaded", function () {
            renderMathInElement(
                document.body, {
                    delimiters: [
                        { left: "$$", right: "$$", display: true },
                        { left: "$", right: "$", display: false }],
                    ignoredTags: [],
                })
        });
    </script>
    <script>
        function getLang(lang) {
            lang = localStorage.getItem("lang");
            if (lang == "ja" || lang == "en") return lang;
            for (e of navigator.languages) {
                if (e.startsWith("en")) return "en";
                if (e.startsWith("ja")) return "ja";
            }
            return "en";
        }
        function refLang() {
            lang = getLang();
            document.getElementById("nav-lang").text = `Lang(${lang})`;

            
            document.querySelectorAll(".lang-en, .lang-ja").forEach(function(e) {
                if (e.classList.contains(`lang-${lang}`)) {
                    e.style.display = 'block';
                } else {
                    e.style.display = 'none';
                }
            })
        }
        function setLang(lang) {
            localStorage.setItem("lang", lang)
            refLang()
        }
        document.addEventListener("DOMContentLoaded", refLang);
    </script>
</head>
'''
html_body = '''
<body>
    <div class="uk-navbar-container" uk-navbar>
        <div class="uk-navbar-right">
            <ul class="uk-navbar-nav">
                <li>
                    <a href="#" id="nav-lang">Lang()</a>
                    <div class="uk-navbar-dropdown">
                        <ul class="uk-nav uk-navbar-dropdown-nav">
                            <li><a href="#" onclick="setLang('ja')">Ja</a></li>
                            <li><a href="#" onclick="setLang('en')">En</a></li>
                        </ul>
                    </div>
                </li>
            </ul>
        </div>
    </div>

    <section class="uk-section">
        <div class="uk-container">
            {}
        </div>
    </section>
</body>
</html>
'''


class ToHTMLConverter:
    def __init__(self, probdir: Path, config):
        logger.info("HTML Generate {}".format(probdir.name))
        md_statement = open(str(probdir / 'task.md'), encoding='utf-8').read()

        # evaluate jinja2
        lang_manager = LangManager()
        environment = Environment(variable_start_string="@{", variable_end_string="}", loader=DictLoader({'task': md_statement}))
        logger.info(environment.list_templates())
        template = environment.get_template('task')
        # environment.globals['endlang'] = lang_manager.reset_lang
        # template = Template(md_statement)
        # template.environment.variable_start_string = "@@"
        # template.environment.variable_end_string = "@@"
        # template.environment.globals['endlang'] = lang_manager.reset_lang

        mid_statement = template.render(
            keyword=keywords,
            param=gen_params(config.get('params', dict())),
            lang=lang_manager,
            example=ExampleReader(problem_dir=probdir),
        )

        # evaluate markdown
        self.statement = markdown(
            mid_statement, extensions=[
                'md_in_html',
                'markdown.extensions.fenced_code',
                ForumExtension(url=config.get('forum', ''))
            ],
        )
        self.html = html_header + html_body.format(self.statement)
