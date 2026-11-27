// Single path (natural labels, DFS depth N_MAX), cycle and star on N_MAX vertices.
#include "planar_gen.h"
#include "../params.h"

int main(int, char* argv[]) {
	int seed = atoi(argv[1]);
	Random gen(seed);
	if (seed % 3 == 0) print_graph(gen, path_graph(N_MAX), false, false, false);
	else if (seed % 3 == 1) print_graph(gen, cycle_graph(N_MAX));
	else print_graph(gen, star_graph(N_MAX));
	return 0;
}
