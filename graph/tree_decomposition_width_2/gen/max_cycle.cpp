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

	int n = min(N_MAX, M_MAX);

	vector<pair<int, int>> edges;
	for(int i=0; i<n-1; i++) edges.emplace_back(i, i+1);
	edges.emplace_back(n-1, 0);
	
	gen.shuffle(edges.begin(), edges.end());

	shuffle_vertices_and_print_graph(gen, n, edges);
	return 0;
}
