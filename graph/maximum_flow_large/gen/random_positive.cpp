#include "../params.h"
#include "network.h"

int main(int, char* argv[]) {
    const int seed = std::atoi(argv[1]);
    Random rng(seed);
    Network g(N_MAX, N_MAX / 3, 2 * N_MAX / 3);
    std::vector<int> path = {g.s};
    for (int v = 0; v < g.n; ++v) if (v != g.s && v != g.t) path.push_back(v);
    path.push_back(g.t);
    for (int i = 0; i + 1 < int(path.size()); ++i) {
        g.add(path[i], path[i + 1], seed == 0 ? 1 : C_MAX);
    }
    while (int(g.edges.size()) < M_MAX) {
        int u = rng.uniform(0, g.n - 1), v = rng.uniform(0, g.n - 1);
        g.add(u, v, seed == 0 ? rng.uniform(0, 1) : mixed_capacity(rng, C_MAX));
    }
    g.permute_vertices(rng);
    g.shuffle_edges(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
