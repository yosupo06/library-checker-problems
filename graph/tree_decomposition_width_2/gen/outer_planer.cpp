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

	int l = 0, r = n - 1;
	while (l < r) {
		if (gen.uniform_bool()) {
			edges.push_back({l, r});
		}
		if (gen.uniform_bool()) {
			l++;
		} else {
			r--;
		}
	}
	gen.shuffle(edges.begin(), edges.end());
	if (int(edges.size()) > M_MAX) edges.resize(M_MAX);

	print_graph(gen, n, edges);
	return 0;
}
