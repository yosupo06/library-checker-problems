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
	int m = n;

	vector<pair<int, int>> edges;
	for(int i=0; i<n-1; i++) edges.emplace_back(i, i+1);
	edges.emplace_back(n-1, 0);

	vector<int> perm(n);
	for(int i=0; i<n; i++) perm[i] = i;
	gen.shuffle(perm.begin(), perm.end());
	for(int i=0; i<m; i++){
		edges[i].first = perm[edges[i].first];
		edges[i].second = perm[edges[i].second];
	}
	
	gen.shuffle(edges.begin(), edges.end());
	
	print_graph(gen, n, edges);
	return 0;
}
