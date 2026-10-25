// A long subdivision of K5 or K3,3 hidden inside a huge planar host (No; sparse, passes the Euler bound).
//   mode 0: K5 subdivision glued to a random deep tree
//   mode 1: K3,3 subdivision as a separate component next to a random deep tree (vertex 0 is in the host)
//   mode 2: K5 subdivision as a separate component next to a path, natural labels
//   mode 3: K3,3 subdivision glued to the end of a path, natural labels
//   seed 0: all four modes with hosts of ~50000 vertices; seed 1: mode 1 at the maximum size
#include "planar_gen.h"
#include "../params.h"

void print_hidden_case(Random& gen, int mode, int host_n, int len_lo, int len_hi) {
	bool k33 = mode % 2 == 1, separate = mode == 1 || mode == 2, path_host = mode >= 2;
	Graph core = k33 ? complete_bipartite(3, 3) : complete_graph(5);
	Graph sub = subdivide_edges(gen, core, len_lo, len_hi);
	Graph g = path_host ? path_graph(host_n) : random_deep_tree(gen, host_n, 3);
	int off = g.add_graph(sub);
	if (!separate) {
		// Glue: connect a random vertex of the subdivision to a random host vertex.
		int sub_v = off + gen.uniform(0, sub.n - 1), host_v = gen.uniform(0, host_n - 1);
		g.add_edge(host_v, sub_v);
	}
	if (path_host) {
		print_case(gen, g, false, false, false);
	} else {
		// Random labels, but vertex 0 must stay in the host.
		auto perm = gen.perm<int>(g.n);
		int host_v = gen.uniform(0, host_n - 1);
		for (int i = 0; i < g.n; i++) if (perm[i] == 0) { std::swap(perm[i], perm[host_v]); break; }
		for (auto& [u, v] : g.edges) { u = perm[u]; v = perm[v]; }
		print_case(gen, g, false, true, true);
	}
}

int main(int, char* argv[]) {
	int64_t seed = atoll(argv[1]);
	Random gen(seed);
	if (seed % 2 == 0) {
		printf("4\n");
		for (int mode = 0; mode < 4; mode++) print_hidden_case(gen, mode, 50000, 100, 300);
	} else {
		printf("1\n");
		int sub_n = 9 * 30000 + 6;  // upper bound on the size of the subdivision
		print_hidden_case(gen, 1, N_MAX - sub_n, 10000, 30000);
	}
	return 0;
}
