#include <vector>
#include <utility>
#include <algorithm>

#include "random.h"
#include "gen_common.hpp"
#include "../params.h"

using namespace std;

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed);

	int ParallelCount = min(N_MAX - 2, M_MAX / 2);
	int n = ParallelCount + 2;
	// int m = ParallelCount * 2;

	vector<pair<int, int>> edges;
	for(int i=0; i<ParallelCount; i++){
		edges.emplace_back(i, ParallelCount);
		edges.emplace_back(i, ParallelCount + 1);
	}

	gen.shuffle(edges.begin(), edges.end());

	shuffle_vertices_and_print_graph(gen, n, edges);
	return 0;
}
