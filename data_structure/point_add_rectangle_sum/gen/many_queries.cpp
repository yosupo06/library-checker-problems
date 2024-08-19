#include <stdio.h>
#include <tuple>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = N_MAX;
	int q = Q_MAX;
	printf("%d %d\n", n, q);
	for (int i = 0; i < n; i++) {
		int x = gen.uniform<int>(0, COORD_MAX);
		int y = gen.uniform<int>(0, COORD_MAX);
		int w = gen.uniform<int>(0, WEIGHT_MAX);
		printf("%d %d %d\n", x, y, w);
	}
	for (int i = 0; i < q; i++) {
		int t = !!gen.uniform<int>(0, 5);
		printf("%d ", t);
		if (t) {
			int l, r;
			std::tie(l, r) = gen.uniform_pair<int>(0, COORD_MAX);
			int d, u;
			std::tie(d, u) = gen.uniform_pair<int>(0, COORD_MAX);
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
