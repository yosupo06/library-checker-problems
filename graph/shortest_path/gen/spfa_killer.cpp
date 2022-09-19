#include <vector>
#include "random.h"
#include "../params.h"
#include "../fastio.h"

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);
	
	int n = -1, m = -1, s = -1, t = -1;
	struct Hen {
		int from;
		int to;
		int cost;
	};
	std::vector<Hen> hens;
	if (seed == 0) {
		/*
			designed to make TLE SPFA with SLF (optionally with fault tolerance) and/or LLL
			consists of three parts :
			 - "main" part where SLF with smaller fault tolerance performs worse
				
				^^^^^
				^^^^^ (`b` edges out from [hub])
				[hub]<<<<<<<<<<<<<<<<<<<<<.
				 ^   \                     \
				 x    .<<<<< x-4 <<<<<<.    .<<<<<<  x-8 <<<<<<.  ...
				 ^                      \                       \
				[0] >> 1 >> [1] >> 2 >> [3] >> 1 >> [4] >> 2 >> [6]  ... (repeats `a` times)
				 v                       v                       v
				 2                       2                       2
				 v                       v                       v
				[2]                     [5]                     [8]
				
			 - "long" part which is the same as almost_line_2 and kills SLF with larger fault tolerance
			 - "distant" part which is a star graph with 10^9-cost edges attached at the start of long part to neutralize LLL
		*/
		int long_part_size = std::min(N_MAX, M_MAX) / 5;
		int dist_part_size = 1000;
		int n_left = N_MAX - long_part_size - dist_part_size;
		int m_left = M_MAX - 2 * long_part_size - dist_part_size;
		int a = std::min(n_left, m_left) / 8;
		int b = std::min(n_left, m_left) / 2;
		n = 3 * a + b + 1 + long_part_size + dist_part_size;
		m = 4 * a - 2 + b + 2 * long_part_size + dist_part_size;
		s = 0;
		t = n - 1;
		int hub = a * 3 + b;
		int long_part_base = n - long_part_size;
		int dist_part_base = n - long_part_size - dist_part_size;
		// main part
		for (int i = 0; i < a; i++) {
			if (i + 1 < a) {
				hens.push_back({i * 3 + 0, i * 3 + 1, 1});
				hens.push_back({i * 3 + 1, i * 3 + 3, 2});
			}
			hens.push_back({i * 3 + 0, i * 3 + 2, 2});
			hens.push_back({i * 3 + 0, hub, 4 * (a - i)});
		}
		for (int i = 0; i < b; i++) hens.push_back({hub, a * 3 + i, 1});
		// long part
		hens.push_back({a * 3, long_part_base, 1});
		for (int i = 0; i + 1 < long_part_size; i++) hens.push_back({long_part_base + i, long_part_base + i + 1, 1});
		std::set<std::pair<int, int> > used;
		for (int i = 0; i < long_part_size; i++) { // add more `long_part_size` edges
			int a, b;
			do {
				a = gen.uniform(0, long_part_size - 3);
				b = a + gen.uniform(2, 3);
			} while (b >= n || !used.insert({a, b}).second);
			hens.push_back({long_part_base + a, long_part_base + b, b - a + gen.uniform(-1, 1)});
		}
		// distant part
		for (int i = 0; i < dist_part_size; i++) hens.push_back({a * 3, dist_part_base + i, (int) C_MAX});
	}
	auto perm = gen.perm<int>(n);
	for (auto &i : hens) i.from = perm[i.from], i.to = perm[i.to];
	s = perm[s];
	t = perm[t];
	
	gen.shuffle(hens.begin(), hens.end());
	
	println(n, ' ', m, ' ', s, ' ', t);
	for (auto i : hens) println(i.from, ' ', i.to, ' ', i.cost);
	return 0;
}
