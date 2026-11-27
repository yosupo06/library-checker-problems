// Uniformly random simple graphs with M around N / 2 (the planarity threshold of random graphs) and above.
#include "planar_gen.h"

int main(int, char* argv[]) {
	Random gen(atoll(argv[1]));
	std::vector<Graph> gs;
	double fs[] = {0.3, 0.45, 0.55, 0.7, 1.0, 1.5};
	int ns[] = {50, 200, 1000, 5000, 20000, 100000};
	auto perm = gen.perm<int>(6);
	for (int i = 0; i < 6; i++) gs.push_back(random_simple_graph(gen, ns[i], int(ns[i] * fs[perm[i]])));
	print_graphs(gen, gs);
	return 0;
}
