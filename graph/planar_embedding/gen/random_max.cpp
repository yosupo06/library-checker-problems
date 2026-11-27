// Uniformly random simple graph with N = N_MAX, M = M_MAX (No).
#include "planar_gen.h"
#include "../params.h"

int main(int, char* argv[]) {
	Random gen(atoll(argv[1]));
	print_graph(gen, random_simple_graph(gen, N_MAX, M_MAX));
	return 0;
}
