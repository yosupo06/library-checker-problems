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

	int n = N_MAX;
	vector<pair<int, int>> edges;

	for (int i = 1; i < n; i++) {
		edges.push_back({gen.uniform(0, i - 1), i});
	}

	print_graph(gen, n, edges);
	return 0;
}
