#include "../params.h"
#include "network.h"

// Zadeh-style construction, with shared hubs as described in network.h.
// https://doi.org/10.1145/321679.321693
// https://codeforces.com/blog/entry/145343
int main(int argc, char* argv[]) {
    const int seed = std::atoi(argv[1]);
    int k = seed == 0 ? 8 : 16;
    int rounds = seed == 0 ? 20 : 27;
    int mode = seed < 2 ? 0 : seed - 1;
    // A wider central bipartite graph; preserve seeds 0..3 exactly.
    if (seed == 4) { k = 101; rounds = 10; mode = 0; }
    // Optional k, rounds, mode permit small structural checks and benchmarks.
    if (argc > 3) { k = std::atoi(argv[2]); rounds = std::atoi(argv[3]); }
    if (argc > 4) mode = std::atoi(argv[4]);
    Network g = zadeh_network(k, rounds);
    Random rng(seed);
    if (mode & 1) g.permute_vertices(rng);
    if (mode & 2) g.shuffle_edges(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
