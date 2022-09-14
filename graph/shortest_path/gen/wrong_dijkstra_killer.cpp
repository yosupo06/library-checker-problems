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
	bool shuffle_vertices = false;
	if (seed == 0) { // for wrong_dijkstra_0
		int one = M_MAX / 4;
		n = one * 2 + 3;
		m = one * 4;
		s = 0;
		t = n - 1;
		
		for (int i = 0; i < one; i++) {
			hens.push_back({0, i + 1, i});
			hens.push_back({i + 1, one + 1, (one - i - 1) * 2});
			hens.push_back({one + 1, one + 2 + i, 2 * i});
			hens.push_back({one + 2 + i, n - 1, one - i - 1});
		}
		shuffle_vertices = false; // for compatibility
	} else if (seed == 1) { // for wrong_dijkstra_3
		/*
			Rough sketch of the graph :
			
			 1 >>(10^9)>> 3>>.
			 ^            ^  v
			(0)	         (0) v   5 >(10^9)/4> 7>>.
			 ^            ^ (0)  ^            ^  |
			 0 >>>(1)>>>> 2   \ (0)	         (0) |
			  \                \ ^            ^ (0)
			   .>>>(10^9)/2>>>>>>4 >>>(1)>>>> 6   \
			                      \                \ 
			                       .>>>(10^9)/8>>>>>>8  ...
		*/
		int k = 15; // log(max cost) / 2
		// one unit uses 4k vertices & 6k edges
		int repeat = std::min(N_MAX / (4 * k), M_MAX / (6 * k));
		n = 4 * k * repeat;
		m = 6 * k * repeat - 2;
		s = 0;
		t = n - 1;
		for (int i = 0; i < repeat; i++) for (int j = 0; j < k; j++) {
			int base = (i * k + j) * 4;
			hens.push_back({base, base + 1, 0});
			hens.push_back({base, base + 2, 1});
			hens.push_back({base + 1, base + 3, (int) (C_MAX >> (j * 2))});
			hens.push_back({base + 2, base + 3, 0});
			if (base + 4 < n) {
				hens.push_back({base, base + 4, (int) (C_MAX >> (j * 2 + 1))});
				hens.push_back({base + 3, base + 4, 0});
			}
		}
		shuffle_vertices = true;
	}
	gen.shuffle(hens.begin(), hens.end()); // always shuffle edges
	if (shuffle_vertices) {
		auto perm = gen.perm<int>(n);
		for (auto &i : hens) i.from = perm[i.from], i.to = perm[i.to];
		s = perm[s];
		t = perm[t];
	}
	
	println(n, ' ', m, ' ', s, ' ', t);
	for (auto i : hens) println(i.from, ' ', i.to, ' ', i.cost);
	return 0;
}
