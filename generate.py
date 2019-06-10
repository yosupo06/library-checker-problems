#!/usr/bin/env python3

import argparse
from sys import argv, exit
import os, shutil
from pathlib import Path
from os import path, chdir, makedirs
from binascii import crc32
from subprocess import run, call, check_call, TimeoutExpired, CalledProcessError, DEVNULL
from datetime import datetime
from termcolor import colored, cprint
import toml

# (random, 1) -> random_01
def casename(name: str, i: int):
	return Path(name).stem + '_' + str(i).zfill(2)

class UnknownTypeFile(Exception):
	def __init__(self, message):
		super().__init__()
		self.message = message

def compile(src: Path):
	if src.suffix == '.cpp':
		check_call(['g++', '-O2', '-std=c++14',
			'-I', Path.cwd() / 'common',
			'-o', src.with_suffix(''),
			src])
	elif src.suffix == '.in':
		pass
	else:
		print('Unknown type of file {}'.format(src))
		raise UnknownTypeFile('Unknown file: {}'.format(src))

def execcmd(src: Path, arg: [str] = []):
	if src.suffix == '.cpp':
		cmd = [src.with_suffix('')]
		cmd.extend(arg)
		return cmd
	elif src.suffix == '.in':
		inpath = src.with_name(casename(src, int(arg[0])) + '.in')
		cmd = ['cat', inpath]
		return cmd
	else:
		raise UnknownTypeFile('Unknown file: {} {}'.format(src, arg))

class Problem:
	basedir: Path()
	config = None	
	def __init__(self, basedir: Path):
		self.basedir = basedir
		self.config = toml.load(basedir / 'info.toml')
	
	def make_inputs(self):
		indir = self.basedir / 'in'
		gendir = self.basedir / 'gen'

		print('[#] clear input {}'.format(indir))
		if indir.exists():
			shutil.rmtree(indir)
		indir.mkdir()
		
		print('[#] compile verify')
		compile(gendir / self.config['verify'])

		for test in self.config['tests']:
			name = test['Name']
			num = test['Number']

			print('[#] case {} {}cases'.format(name, num))
			print('[#] compile')
			compile(gendir / name)

			for i in range(num):
				# output filename
				inpath = indir / (casename(name, i) + '.in')
				check_call(execcmd(gendir / name, [str(i)]), stdout=open(inpath, 'w'))
				check_call(execcmd(gendir / self.config['verify']), stdin=open(inpath, 'r'))

	def make_outputs(self):
		indir = self.basedir / 'in'
		outdir = self.basedir / 'out'
		soldir = self.basedir / 'sol'

		print('[#] clear output {}'.format(outdir))
		if outdir.exists():
			shutil.rmtree(outdir)
		outdir.mkdir()

		print('[#] compile sol')
		compile(soldir / self.config['solution'])

		for test in self.config['tests']:
			name = test['Name']
			num = test['Number']

			for i in range(num):
				inpath = indir / (casename(name, i) + '.in')
				outpath = outdir / (casename(name, i) + '.out')
				print('# start ' + casename(name, i) + '...')
				check_call(execcmd(soldir / self.config['solution']),
								stdin=open(inpath, 'r'), stdout=open(outpath, 'w'))


parser = argparse.ArgumentParser(description='Testcase Generator')
parser.add_argument('toml', help='Toml File')
args = parser.parse_args()

problems = toml.load(args.toml)

for probinfo in problems['Problems']:
	print('[*] Start {}'.format(probinfo['Dir']))
	problem = Problem(Path.cwd() / probinfo['Dir'])

	problem.make_inputs()
	problem.make_outputs()
