#include <stdio.h>
#include <tuple>
#include "random.h"
#include "../params.h"

#define SMALL_N_MAX 1000
#define SMALL_Q_MAX 1000
#define SMALL_COORD_MAX 1000
#define SMALL_WEIGHT_MAX 1000

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = gen.uniform(1, SMALL_N_MAX);
	int q = gen.uniform(1, SMALL_Q_MAX);
	printf("%d %d\n", n, q);
	for (int i = 0; i < n; i++) {
		int x = gen.uniform(0, SMALL_COORD_MAX);
		int y = gen.uniform(0, SMALL_COORD_MAX);
		int w = gen.uniform(0, SMALL_WEIGHT_MAX);
		printf("%d %d %d\n", x, y, w);
	}
	for (int i = 0; i < q; i++) {
		int t = gen.uniform<int>(0, 1);
		printf("%d ", t);
		if (t) {
			int l, r;
			std::tie(l, r) = gen.uniform_pair<int>(0, SMALL_COORD_MAX);
			int d, u;
			std::tie(d, u) = gen.uniform_pair<int>(0, SMALL_COORD_MAX);
			printf("%d %d %d %d\n", l, d, r, u);
		} else {
			int x = gen.uniform(0, SMALL_COORD_MAX);
			int y = gen.uniform(0, SMALL_COORD_MAX);
			int w = gen.uniform(0, SMALL_WEIGHT_MAX);
			printf("%d %d %d\n", x, y, w);
		}
	}
	return 0;
}
