// Classic named graphs, ladders / prisms / Moebius ladders (sparse No passing the Euler bound), grids with holes.
#include "planar_gen.h"

Graph minus_edge(Graph g, int idx) { g.edges.erase(g.edges.begin() + idx); return g; }
Graph minus_vertex(Graph g, int v) {
	Graph h; h.add_vertices(g.n - 1);
	for (auto [a, b] : g.edges) {
		if (a == v || b == v) continue;
		h.add_edge(a - (a > v), b - (b > v));
	}
	return h;
}

int main(int, char* argv[]) {
	Random gen(atoll(argv[1]));
	std::vector<Graph> gs = {
		petersen_graph(),                                              // No (no K5 / K3,3 subgraph)
		moebius_ladder(8), moebius_ladder(10),                         // Wagner graph V8, No
		goldner_harary_graph(),                                        // Yes (maximal planar)
		grotzsch_graph(),                                              // No
		wheel_graph(7), prism_graph(5),                                // Yes
		minus_edge(complete_graph(5), gen.uniform(0, 9)),              // K5 - e, Yes
		minus_edge(complete_bipartite(3, 3), gen.uniform(0, 8)),       // K3,3 - e, Yes
		minus_edge(complete_graph(6), gen.uniform(0, 14)),             // K6 - e, No
		icosahedron_graph(), dodecahedron_graph(), octahedron_graph(), // Yes
		heawood_graph(),                                               // No
		hypercube_graph(3), hypercube_graph(4),                        // Yes, No
		minus_edge(petersen_graph(), gen.uniform(0, 14)),              // Petersen - e
		minus_vertex(petersen_graph(), gen.uniform(0, 9)),             // Petersen - v, No
		moebius_ladder(1000), moebius_ladder(40000),                   // No
		ladder_graph(20000), prism_graph(20000),                       // Yes
		grid_graph(gen, 3, 1000), grid_graph(gen, 300, 300), grid_graph(gen, 300, 300, 0.15),
	};
	print_graphs(gen, gs);
	return 0;
}
