#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int one = M_MAX / 4;
	int n = one * 2 + 3;
	int m = one * 4;
	
	printf("%d %d %d %d\n", n, m, 0, n - 1);
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	for (int i = 0; i < one; i++) {
		hens.push_back({0, i + 1, i});
		hens.push_back({i + 1, one + 1, (one - i - 1) * 2});
		hens.push_back({one + 1, one + 2 + i, 2 * i});
		hens.push_back({one + 2 + i, n - 1, one - i - 1});
	}
	gen.shuffle(hens.begin(), hens.end());
	
	for (auto i : hens) printf("%d %d %d\n", i.from, i.to, i.cost);
	return 0;
}
