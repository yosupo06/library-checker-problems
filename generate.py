#!/usr/bin/env python3

import argparse
from sys import argv, exit
import os, shutil
from os import path, chdir, makedirs
from binascii import crc32
from subprocess import run, call, check_call, TimeoutExpired, CalledProcessError, DEVNULL
from datetime import datetime
from termcolor import colored, cprint
import toml

parser = argparse.ArgumentParser(description='Testcase Generator')
parser.add_argument('toml', help='Toml File')

args = parser.parse_args()

tomlpath = os.path.abspath(args.toml)
problems = toml.load(tomlpath)

curdir = os.path.dirname(tomlpath)

def casename(testname, i):
	testtitle, _ = os.path.splitext(testname)
	return testtitle + '_' + str(i).zfill(2)

# source must be abspath
def compilecxx(srcpath):
	dirname, srcname = os.path.split(srcpath)
	srctitle, _ = os.path.splitext(srcname)
	chdir(dirname)
	check_call(['g++', '-O2', '-std=c++14',
		'-I', os.path.join(curdir, 'common'),
		srcname, '-o', srctitle])

def execcmdcxx(srcpath):
	srctitle, _ = os.path.splitext(srcpath)
	return srctitle

def casemake(problemdir, config):
	# clear in
	indir = os.path.join(problemdir, 'in')
	print('[#] clear {}'.format(indir))
	if os.path.exists(indir):
		shutil.rmtree(indir)
	makedirs(indir, exist_ok=True)

	# make verify
	gendir = os.path.join(problemdir, 'gen')
	print('[#] compile verify')
	compilecxx(os.path.join(gendir, config['verify']))
	
	for test in config['tests']:
		testname = test['Name']
		testnum = test['Number']
		istext = ('Text' in test) and test['Text']

		print('[#] case {} {}cases'.format(testname, testnum))

		if not istext:
			# make gen
			compilecxx(os.path.join(gendir, testname))
			print('[#] compile {}'.format(testname))

		for i in range(testnum):
			# output filename
			casepath = os.path.join(indir, casename(testname, i) + '.in')

			if istext:
				# input filename
				textpath = os.path.join(gendir, casename(testname, i) + '.in')
				shutil.copy(textpath, casepath)
			else:
				check_call([execcmdcxx(os.path.join(gendir, testname)), str(i)], stdout=open(casepath, 'w'))
			# run verify
			check_call([execcmdcxx(os.path.join(gendir, config['verify']))], stdin=open(casepath, 'r'))

def solmake(problemdir, config):
	# clear out
	outdir = os.path.join(problemdir, 'out')
	print('[#] clear {}'.format(outdir))
	if os.path.exists(outdir):
		shutil.rmtree(outdir)
	makedirs(outdir, exist_ok=True)

	# make answer
	soldir = os.path.join(problemdir, 'sol')
	print('[#] compile sol')
	compilecxx(os.path.join(soldir, config['solution']))

	for test in config['tests']:
		testname = test['Name']
		testnum = test['Number']
		for i in range(testnum):
			infile = os.path.join(problemdir, 'in', casename(testname, i) + '.in')
			outfile = os.path.join(problemdir, 'out', casename(testname, i) + '.out')
			print('# start ' + casename(testname, i) + '...')
			check_call([execcmdcxx(os.path.join(soldir, config['solution']))],
				stdin=open(infile, 'r'), stdout=open(outfile, 'w'))

for problem in problems['Problems']:
	problemdir = os.path.join(curdir, problem['Dir'])
	config = toml.load(os.path.join(problemdir, 'info.toml'))
	casemake(problemdir, config)
	solmake(problemdir, config)
