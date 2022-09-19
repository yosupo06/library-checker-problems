#include <vector>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = N_MAX, m = -1, s = -1, t = -1;
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	
	if (seed == 0) {
		m = n - 1;
		s = 0;
		t = n - 1;
		
		int k = gen.uniform(5, 100);
		for (int i = 1; i < n; i++) {
			if (i < n - k) hens.push_back({0, i, (int) gen.uniform(C_MIN, C_MAX)});
			else if (i == n - k) hens.push_back({n - k - 1, i, (int) gen.uniform(C_MIN, C_MAX)});
			else {
				int from = gen.uniform(n - k, i - 1);
				hens.push_back({from, i, (int) gen.uniform(C_MIN, C_MAX)});
			}
		}
	} else if (seed == 1) {
		m = n - 1;
		s = 0;
		t = 2;
		for (int i = 1; i < n; i++) {
			if (i & 1) hens.push_back({0, i, (int) gen.uniform(C_MIN, C_MAX)});
			else hens.push_back({i - 1, i, (int) gen.uniform(C_MIN, C_MAX)});
		}
	}
	
	auto perm = gen.perm<int>(n);
	s = perm[s];
	t = perm[t];
	for (auto &i : hens) i.from = perm[i.from], i.to = perm[i.to];
	
	gen.shuffle(hens.begin(), hens.end());
	
	println(n, ' ', m, ' ', s, ' ', t);
	for (auto i : hens) println(i.from, ' ', i.to, ' ', i.cost);
	return 0;
}
