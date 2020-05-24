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
	int m = M_MAX;

	set<pair<int, int>> used;

	for (int i = 0; i < m; i++) {
		int a, b;
		do {
			tie(a, b) = gen.uniform_pair(0, n - 1);
		} while (used.count({a, b}));
		used.insert({a, b});
	}

	print_graph(gen, n, {used.begin(), used.end()});
	return 0;
}
