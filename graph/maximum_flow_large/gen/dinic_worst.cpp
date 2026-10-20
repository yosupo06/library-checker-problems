#include "../params.h"
#include "network.h"

// Zadeh-style construction, with shared hubs as described in network.h.
// https://doi.org/10.1145/321679.321693
// https://codeforces.com/blog/entry/145343
int main(int argc, char* argv[]) {
    const int seed = std::atoi(argv[1]);
    int k = seed == 0 ? 32 : (seed == 1 ? 40 : 64);
    int rounds = seed == 0 ? 100 : (seed == 1 ? 200 : 482);
    int mode = seed < 3 ? 0 : seed - 2;
    if (argc > 3) { k = std::atoi(argv[2]); rounds = std::atoi(argv[3]); }
    if (argc > 4) mode = std::atoi(argv[4]);
    Network g = zadeh_network(k, rounds);
    Random rng(seed);
    if (mode & 1) g.permute_vertices(rng);
    if (mode & 2) g.shuffle_edges(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
