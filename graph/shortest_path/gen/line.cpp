#include <vector>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

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
	
	auto perm = gen.perm<int>(n);
	s = perm[s];
	t = perm[t];
	for (auto &i : hens) i.from = perm[i.from], i.to = perm[i.to];
	
	gen.shuffle(hens.begin(), hens.end());
	
	println(n, ' ', m, ' ', s, ' ', t);
	for (auto i : hens) println(i.from, ' ', i.to, ' ', i.cost);
	return 0;
}
