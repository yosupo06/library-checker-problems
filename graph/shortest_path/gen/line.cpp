#include <stdio.h>
#include "random.h"
#include "../params.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int len = std::min(N_MAX - 1, M_MAX);
	int n = len + 1;
	int m = len;
	int s = 0;
	int t = n - 1;
	
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	for (int i = 0; i < len; i++) hens.push_back({i, i + 1, C_MAX});
	// shuffle vertex
	std::vector<int> perm(n);
	std::iota(perm.begin(), perm.end(), 0);
	gen.shuffle(perm.begin(), perm.end());
	s = perm[s];
	t = perm[t];
	for (auto &i : hens) i.from = perm[i.from], i.to = perm[i.to];
	
	gen.shuffle(hens.begin(), hens.end());
	
	printf("%d %d %d %d\n", n, m, s, t);
	for (auto i : hens) printf("%d %d %d\n", i.from, i.to, i.cost);
	return 0;
}
