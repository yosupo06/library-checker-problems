// T = T_MAX tiny random graphs (sum of N close to N_MAX): catches per-case
// work proportional to N_MAX instead of N.
#include "planar_gen.h"
#include "../params.h"

int main(int, char* argv[]) {
	int64_t seed = atoll(argv[1]);
	Random gen(seed);
	const int T = int(T_MAX);
	const int n_budget = int(N_MAX), m_budget = int(M_MAX);
	const int avg_n = n_budget / T, avg_m = m_budget / T;
	std::vector<Graph> gs;
	int n_sum = 0, m_sum = 0;
	for (int t = 0; t < T; t++) {
		int remaining = T - t - 1;
		int n = seed % 2 == 1 ? avg_n : gen.uniform(1, 2 * avg_n - 2);
		n = std::min(n, n_budget - n_sum - remaining);
		int maxm = std::min(n * (n - 1) / 2, avg_m);
		int m = gen.uniform(0, maxm);
		n_sum += n; m_sum += m;
		assert(n_sum <= n_budget && m_sum <= m_budget);
		Graph g; g.add_vertices(n);
		if (m > 0) add_random_nonedges(gen, g, m);
		gs.push_back(g);
	}
	print_graphs(gen, gs);
	return 0;
}
