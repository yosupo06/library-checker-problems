#include <stdio.h>
#include <vector>
#include "random.h"
#include "../params.h"

#define BLOCK 1000

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	std::vector<int> xs, ys;
	for (int i = 0; i < BLOCK; i++) {
		xs.push_back(gen.uniform<int>(0, COORD_MAX - 1));
		ys.push_back(gen.uniform<int>(0, COORD_MAX - 1));
	}
	std::sort(xs.begin(), xs.end());
	std::sort(ys.begin(), ys.end());
	xs.push_back(COORD_MAX);
	ys.push_back(COORD_MAX);
	
	int n = N_MAX;
	int q = Q_MAX;
	printf("%d %d\n", n, q);
	
	for (int i = 0; i < n; i++) {
		int x = xs[gen.uniform(0, BLOCK - 1)];
		int y = ys[gen.uniform(0, BLOCK - 1)];
		int w = gen.uniform<int>(0, WEIGHT_MAX);
		printf("%d %d %d\n", x, y, w);
	}
	
	for (int i = 0; i < q; i++) {
		int t = gen.uniform(0, 1);
		printf("%d ", t);
		if (t) {
			int l = gen.uniform<int>(0, BLOCK - 1);
			int r = gen.uniform<int>(l + 1, BLOCK);
			int d = gen.uniform<int>(0, BLOCK - 1);
			int u = gen.uniform<int>(d + 1, BLOCK);
			printf("%d %d %d %d\n", xs[l], ys[d], xs[r], ys[u]);
		} else {
			int x = gen.uniform<int>(0, BLOCK - 1);
			int y = gen.uniform<int>(0, BLOCK - 1);
			int w = gen.uniform<int>(0, WEIGHT_MAX);
			printf("%d %d %d\n", xs[x], ys[y], w);
		}
	}
	return 0;
}
