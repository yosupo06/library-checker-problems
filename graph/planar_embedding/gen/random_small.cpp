// Uniformly random simple graphs with 5 <= N <= 12: half of the cases with a uniformly random
// number of edges, half with N <= M <= 3N (around the planarity threshold).
#include "planar_gen.h"

int main(int, char* argv[]) {
	Random gen(atoll(argv[1]));
	std::vector<Graph> gs;
	for (int t = 0; t < 10000; t++) {
		int n = gen.uniform(5, 12);
		int maxm = n * (n - 1) / 2;
		int m = t % 2 == 0 ? gen.uniform(0, maxm) : gen.uniform(std::min(maxm, n), std::min(maxm, 3 * n));
		gs.push_back(random_simple_graph(gen, n, m));
	}
	print_graphs(gen, gs);
	return 0;
}
