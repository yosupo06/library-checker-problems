#include <vector>
#include <utility>

#include "random.h"
#include "gen_common.hpp"
#include "../params.h"

using namespace std;

int main(int, char **argv) {
	long long seed = atoll(argv[1]);
	auto gen = Random(seed + 1'000'000);

	int n = gen.uniform<int>(1, N_MAX);
	vector<pair<int, int>> edges;

	// l moves 0 -> m
	// r moves n-1 -> m+1
	// the graph has 2 lines (0 to m) and (n-1 to m+1) , and bipertite graph between them
	int l = 0, r = n - 1;
	// while (l < r) : NG
	//     at the final iteration, generates (l,r) twice
	while (l+1 < r) {
		if (gen.uniform_bool()) {
			edges.push_back({l, r});
		}
		if (gen.uniform_bool()) {
			edges.push_back({l, l+1});
			l++;
		} else {
			edges.push_back({r-1, r});
			r--;
		}
	}
	gen.shuffle(edges.begin(), edges.end());
	if (int(edges.size()) > M_MAX) edges.resize(M_MAX);

	shuffle_vertices_and_print_graph(gen, n, edges);
	return 0;
}
