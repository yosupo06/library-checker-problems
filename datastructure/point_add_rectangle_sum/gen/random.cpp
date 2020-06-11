#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = gen.uniform<int>(1, N_MAX);
	int q = gen.uniform<int>(1, Q_MAX);
	printf("%d %d\n", n, q);
	for (int i = 0; i < n; i++) {
		int x = gen.uniform<int>(0, COORD_MAX);
		int y = gen.uniform<int>(0, COORD_MAX);
		int w = gen.uniform<int>(0, WEIGHT_MAX);
		printf("%d %d %d\n", x, y, w);
	}
	for (int i = 0; i < q; i++) {
		int t = gen.uniform<int>(0, 1);
		printf("%d ", t);
		if (t) {
			int l = gen.uniform<int>(0, COORD_MAX - 1);
			int r = gen.uniform<int>(l + 1, COORD_MAX);
			int d = gen.uniform<int>(0, COORD_MAX - 1);
			int u = gen.uniform<int>(d + 1, COORD_MAX);
			printf("%d %d %d %d\n", l, d, r, u);
		} else {
			int x = gen.uniform<int>(0, COORD_MAX);
			int y = gen.uniform<int>(0, COORD_MAX);
			int w = gen.uniform<int>(0, WEIGHT_MAX);
			printf("%d %d %d\n", x, y, w);
		}
	}
	return 0;
}
