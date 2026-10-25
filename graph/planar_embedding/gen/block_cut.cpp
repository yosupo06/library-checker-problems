// Many small biconnected blocks (triangles, K4, wheels, small triangulations,
// cycles, bridges) glued at cut vertices into a random block-cut tree (Yes).
// One case per size is planar; the other replaces one random block by K5 or the Petersen graph (No).
#include "planar_gen.h"

Graph block_graph(Random& gen, int target, bool bad) {
	Graph g; g.add_vertex();
	std::vector<Graph> blocks;
	while (g.n < target) {
		Graph b;
		switch (gen.uniform(0, 5)) {
			case 0: b = cycle_graph(3); break;
			case 1: b = complete_graph(4); break;
			case 2: b = wheel_graph(gen.uniform(5, 12)); break;
			case 3: b = random_triangulation(gen, gen.uniform(4, 30), 200); break;
			case 4: b = cycle_graph(gen.uniform(3, 20)); break;
			default: b = path_graph(2); break;
		}
		blocks.push_back(b);
		g.n += b.n - 1;
	}
	if (bad) blocks[gen.uniform<int>(0, int(blocks.size()) - 1)] = gen.uniform_bool() ? complete_graph(5) : petersen_graph();
	g = Graph(); g.add_vertex();
	for (auto& b : blocks) {
		// Identify vertex 0 of the block with a random existing vertex.
		int cut = gen.uniform(0, g.n - 1);
		int off = g.add_vertices(b.n - 1) - 1;
		for (auto [u, v] : b.edges) g.add_edge(u == 0 ? cut : u + off, v == 0 ? cut : v + off);
	}
	return g;
}

int main(int, char* argv[]) {
	Random gen(atoll(argv[1]));
	std::vector<Graph> gs;
	for (int target : {10000, 100000}) {
		gs.push_back(block_graph(gen, target, false));
		gs.push_back(block_graph(gen, target, true));
	}
	print_graphs(gen, gs);
	return 0;
}
