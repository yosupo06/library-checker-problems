// Random planar families: Apollonian networks, 2-trees (+ two non-edges: usually No, M = 2N - 1 passes
// the Euler bound), cacti, maximal outerplanar graphs (+ one non-edge).
#include "planar_gen.h"

int main(int, char* argv[]) {
	Random gen(atoll(argv[1]));
	std::vector<Graph> gs;
	for (int n : {1000, 50000}) {
		gs.push_back(random_apollonian(gen, n));
		Graph t = random_two_tree(gen, n);
		gs.push_back(t);
		add_random_nonedges(gen, t, 2);
		gs.push_back(t);
		gs.push_back(random_cactus(gen, n, n < 10000 ? 20 : 10));
		Graph o = random_maximal_outerplanar(gen, n);
		gs.push_back(o);
		add_random_nonedges(gen, o, 1);
		gs.push_back(o);
	}
	print_graphs(gen, gs);
	return 0;
}
