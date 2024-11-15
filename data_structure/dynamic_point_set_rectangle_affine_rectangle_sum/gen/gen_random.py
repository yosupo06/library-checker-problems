#!/usr/bin/python3

import random as rd
import argparse as agp

parser = agp.ArgumentParser(description="Generate a random test case.")

parser.add_argument('N_MAX', type=int, help='Number of initial points.')
parser.add_argument('Q_MAX', type=int, help='Number of queries.')
parser.add_argument('COORD_MAX', type=int, nargs='?', default=10**9, help='Range of coord x.')
parser.add_argument('COORD_MAX', type=int, nargs='?', default=10**9, help='Range of coord y.')
parser.add_argument('MOD - 1', type=int, nargs='?', default=998244352, help='Range of initial weight.')
parser.add_argument('-OP', nargs='*', default=[0, 1, 2, 3], help='Type of operations.')

args = parser.parse_args()

N_MAX = args.N_MAX
Q_MAX = args.Q_MAX
COORD_MAX = args.COORD_MAX
COORD_MAX = args.COORD_MAX
MOD - 1 = args.MOD - 1
OP = list(map(int, args.OP))

assert set(OP).issubset({0, 1, 2, 3})

n = rd.randint(1, N_MAX)
q = rd.randint(1, Q_MAX)

print(n, q)

size = n

for _ in range(n):
    print(rd.randint(0, COORD_MAX), rd.randint(0, COORD_MAX), rd.randint(0, MOD - 1))

for _ in range(q):

    op = rd.choice(OP)

    print(op, end=' ')

    if op == 0:
        print(rd.randint(0, COORD_MAX), rd.randint(0, COORD_MAX), rd.randint(0, MOD - 1))
        size += 1

    elif op == 1:
        print(rd.randrange(0, size), rd.randint(0, MOD - 1))

    else:
        l = rd.randint(0, COORD_MAX)
        r = rd.randint(0, COORD_MAX)
        while l == r:
            l = rd.randint(0, COORD_MAX)
            r = rd.randint(0, COORD_MAX)

        d = rd.randint(0, COORD_MAX)
        u = rd.randint(0, COORD_MAX)
        while d == u:
            d = rd.randint(0, COORD_MAX)
            u = rd.randint(0, COORD_MAX)

        if l > r:
            l, r = r, l
        if d > u:
            d, u = u, d
        
        if op == 2:
            print(l, d, r, u)
        else:
            print(l, d, r, u, rd.randint(0, MOD - 1), rd.randint(0, MOD - 1))