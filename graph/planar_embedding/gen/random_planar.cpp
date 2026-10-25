// Large random planar graphs: random edge subsets of random triangulations / 2-trees.
//   seed 0: Apollonian network on N_MAX vertices, N_MAX edges kept (Yes)
//   seed 1: flip triangulation on 333334 vertices, M_MAX edges kept (Yes)
//   seed 2: as seed 0 plus one random non-edge (usually No; passes the Euler bound)
//   seed 3: smaller subsets plus a few random non-edges (usually No)
#include "planar_gen.h"
#include "../params.h"

int main(int, char* argv[]) {
	int seed = atoi(argv[1]);
	Random gen(seed);
	if (seed == 3) {
		std::vector<Graph> gs;
		std::array<int, 2> nk[] = {{1000, 2}, {50000, 1}, {100000, 1}, {100000, 3}};
		for (int i = 0; i < 4; i++) {
			auto [n, k] = nk[i];
			Graph g;
			if (i % 2 == 0) g = random_edge_subset(gen, random_triangulation(gen, n, int64_t(3) * n), 0.5);
			else g = random_edge_subset(gen, random_two_tree(gen, n), 0.9);
			add_random_nonedges(gen, g, k);
			gs.push_back(g);
		}
		print_graphs(gen, gs);
		return 0;
	}
	Graph g;
	if (seed == 1) {
		g = random_edge_sample(gen, random_triangulation(gen, 333334, int64_t(4) * 333334), int(M_MAX));
	} else {
		g = random_edge_sample(gen, random_apollonian(gen, int(N_MAX)), int(N_MAX) - (seed == 2));
		if (seed == 2) add_random_nonedges(gen, g, 1);
	}
	print_graph(gen, g);
	return 0;
}
