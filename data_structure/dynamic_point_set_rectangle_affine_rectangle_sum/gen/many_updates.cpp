// Adapted from gen_random.py

#include <stdio.h>
#include <tuple>
#include "random.h"
#include "../params.h"

const int OP[] = {1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 2, 3};

int main(int, char **argv) 
{
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = N_MAX;
	int q = Q_MAX;
	printf("%d %d\n", n, q);

    for (int i = 0; i < n; ++i) {
        int x = gen.uniform<int>(0, COORD_MAX);
        int y = gen.uniform<int>(0, COORD_MAX);
        int w = gen.uniform<int>(0, MOD - 1);
		printf("%d %d %d\n", x, y, w);
    }

    for (int i = 0; i < q; ++i) {
        int op = OP[gen.uniform<int>(0, sizeof(OP) / 4 - 1)];
		printf("%d ", op);
        if (op == 0) {
            int x = gen.uniform<int>(0, COORD_MAX);
            int y = gen.uniform<int>(0, COORD_MAX);
            int w = gen.uniform<int>(0, MOD - 1);
			printf("%d %d %d\n", x, y, w);
            ++n;
        } 
		else if (op == 1) {
            int idx = gen.uniform<int>(0, n - 1);
            int w = gen.uniform<int>(0, MOD - 1);
			printf("%d %d\n", idx, w);
        } 
		else {
			auto [l, r] = gen.uniform_pair<int>(0, COORD_MAX);
			auto [d, u] = gen.uniform_pair<int>(0, COORD_MAX);

            if (op == 2) {
				printf("%d %d %d %d\n", l, d, r, u);
            } 
			else { // op == 3
                int a = gen.uniform<int>(0, MOD - 1);
                int b = gen.uniform<int>(0, MOD - 1);
				printf("%d %d %d %d %d %d\n", l, d, r, u, a, b);
            }
        }
    }
	return 0;
}