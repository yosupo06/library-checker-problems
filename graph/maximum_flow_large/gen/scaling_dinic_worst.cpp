#include "../params.h"
#include "network.h"

// Alternating rails as in the Zadeh/MiSawa constructions:
// https://gist.github.com/MiSawa/8016ff5023c2c43d7416fdd426bdd9f7
// This variant reuses parallel core arcs of capacities 1, 2, ..., 2^(bits-1)
// at every scaling threshold, rather than nesting a gadget per threshold.
// Ascending core capacities and stage arcs before rail arcs are essential.
// For the reference scaling Dinic, there are rounds * bits BFS phases.
// N = 2*rounds+2, M = 4*rounds+bits-2, F = rounds*(2^bits-1).
int main(int argc, char* argv[]) {
    Random rng(std::atoll(argv[1]));
    // Optional parameters permit small exhaustive checks.
    const int rounds = argc > 3 ? std::atoi(argv[2]) : 2490;
    const int bits = argc > 3 ? std::atoi(argv[3]) : 18;
    assert(rounds >= 1 && 1 <= bits && bits <= 29);
    const long long capacity = (1LL << bits) - 1;
    assert(rounds * capacity <= C_MAX);
    const int a = 2 * rounds, b = a + 1;
    Network g(b + 1, 0, rounds);
    for (int bit = 0; bit < bits; ++bit) g.add(a, b, 1LL << bit);
    const auto order = rng.perm<int>(rounds);
    for (int i : order) {
        g.add(i, i % 2 == 0 ? a : b, capacity);
        g.add(i % 2 == 0 ? b : a, rounds + i, capacity);
    }
    for (int i = 0; i + 1 < rounds; ++i) {
        g.add(i, i + 1, C_MAX);
        g.add(rounds + i + 1, rounds + i, C_MAX);
    }
    g.permute_vertices(rng);
    assert(g.n == 2 * rounds + 2);
    assert(int(g.edges.size()) == 4 * rounds + bits - 2);
    g.print(N_MAX, M_MAX, C_MAX);
}
