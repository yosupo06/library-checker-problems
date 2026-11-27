// Complete and complete bipartite graphs.
//   seed 0: K_6, K_8, K_50 (No), K_{3,3} (No), K_{2,3000} (Yes), K_{3,300}, K_{100,100} (No) in one file
//   seed 1: K_1414 (No, M = 998991)
//   seed 2: K_{2,500000} (Yes, M = M_MAX)
#include "planar_gen.h"
#include "../params.h"

int main(int, char* argv[]) {
	int64_t seed = atoll(argv[1]);
	Random gen(seed);
	std::vector<Graph> gs;
	switch (seed % 3) {
		case 0:
			gs = {complete_graph(6), complete_graph(8), complete_graph(50), complete_bipartite(3, 3),
			      complete_bipartite(2, 3000), complete_bipartite(3, 300), complete_bipartite(100, 100)};
			break;
		case 1: gs = {complete_graph(1414)}; break;
		default: gs = {complete_bipartite(2, 500000)}; break;
	}
	int64_t tot = 0;
	for (auto& g : gs) tot += int(g.edges.size());
	assert(tot <= M_MAX);
	print_graphs(gen, gs);
	return 0;
}
