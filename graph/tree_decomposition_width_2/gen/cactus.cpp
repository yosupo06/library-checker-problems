#include <vector>
#include <set>
#include <utility>
#include <tuple>

#include "random.h"
#include "gen_common.hpp"
#include "../params.h"

using namespace std;

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int n = gen.uniform<int>(1, N_MAX);
	vector<pair<int, int>> edges;

	int l = 1;
	while (l < n) {
		int r = gen.uniform(l + 2, min(l + 100, n));
		if (r == n - 1) r = n;
		int s = gen.uniform(0, l - 1);
		edges.push_back({s, l});
		for (int i = l; i < r - 1; i++) {
			edges.push_back({i, i + 1});
		}
		edges.push_back({r - 1, s});
		l = r;
	}
	if (edges.size() > M_MAX) edges.resize(M_MAX);

	print_graph(gen, n, edges);
	return 0;
}
