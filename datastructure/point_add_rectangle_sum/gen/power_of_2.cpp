#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = 1;
	for (; n + n <= N_MAX; n <<= 1);
	int q = 1;
	for (; q + q <= Q_MAX; q <<= 1);
	
	printf("%d %d\n", n, q);
	std::set<int> xs, ys;
	for (int i = 0; i < n; i++) {
		int x, y;
		do x = gen.uniform<int>(0, COORD_MAX); while (!xs.insert(x).second);
		do y = gen.uniform<int>(0, COORD_MAX); while (!ys.insert(y).second);
		int w = gen.uniform<int>(0, WEIGHT_MAX);
		printf("%d %d %d\n", x, y, w);
	}
	for (int i = 0; i < q; i++) {
		int l, r;
		do {
			l = gen.uniform<int>(0, COORD_MAX - 1);
			r = gen.uniform<int>(l + 1, COORD_MAX);
		} while (xs.count(l) || xs.count(r));
		xs.insert(l);
		xs.insert(r);
		int d, u;
		do {
			d = gen.uniform<int>(0, COORD_MAX - 1);
			u = gen.uniform<int>(d + 1, COORD_MAX);
		} while (ys.count(d) || ys.count(u));
		ys.insert(d);
		ys.insert(u);
		printf("1 %d %d %d %d\n", l, d, r, u);
	}
	return 0;
}
