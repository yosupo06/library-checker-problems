#include <vector>
#include <set>
#include <utility>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int len = std::min(N_MAX - 1, M_MAX / 2);
	int n = len + 1;
	int m = M_MAX;
	int s = 0;
	int t = n - 1;
	
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	for (int i = 0; i < len; i++) hens.push_back({i, i + 1, (int) gen.uniform(C_MIN, C_MAX)});
	std::set<std::pair<int, int> > used;
	for (int i = len; i < m; i++) {
		int a, b;
		do {
			a = gen.uniform(0, n - 3);
			do b = a + gen.uniform(2, 3); while (b < 0 || b >= n || a == b);
			if (gen.uniform_bool()) std::swap(a, b);
		} while (!used.insert({a, b}).second);
		int c = gen.uniform(C_MIN, C_MAX);
		hens.push_back({a, b, c});
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
