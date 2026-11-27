// A cycle with laminar chords inside and outside (Yes), and the same plus one random extra chord (usually No).
//   seed 0: N = 2000 and 50000, both variants; seed 1: N = 333333 (Yes, M = ~950000)
#include "planar_gen.h"
#include "../params.h"

Graph chorded_cycle(Random& gen, int n) {
	Graph g = random_maximal_outerplanar(gen, n);
	Graph outside = random_maximal_outerplanar(gen, n);
	for (size_t i = n; i < outside.edges.size(); i++) g.edges.push_back(outside.edges[i]);
	dedup(g);
	return g;
}

int main(int, char* argv[]) {
	int64_t seed = atoll(argv[1]);
	Random gen(seed);
	std::vector<Graph> gs;
	if (seed % 2 == 0) {
		for (int n : {2000, 50000}) {
			Graph g = chorded_cycle(gen, n);
			gs.push_back(g);
			add_random_nonedges(gen, g, 1);
			gs.push_back(g);
		}
	} else {
		gs.push_back(chorded_cycle(gen, 333333));
	}
	int64_t tot = 0;
	for (auto& g : gs) tot += int(g.edges.size());
	assert(tot <= M_MAX);
	print_graphs(gen, gs);
	return 0;
}
