#include "../params.h"
#include "network.h"

// Weininger's Anti-Scaling-DFS construction (CC0):
// https://codeforces.com/blog/entry/145343
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_scaling_dfs.cpp
// The recursive DFS gadgets use Dean-Goemans-Immorlica (2006):
// https://doi.org/10.1007/11841036_26
// Each threshold sends width^2 paths through a fresh recursive gadget.
// Keep edge order: residual reverse arcs are needed to reuse each gadget.
int main(int argc, char* argv[]) {
    Random rng(std::atoll(argv[1]));
    const int bits = argc > 3 ? std::atoi(argv[2]) : 17;
    const int width = argc > 3 ? std::atoi(argv[3]) : 93;
    assert(1 <= bits && bits <= 29 && width >= 1);
    Network g(2, 0, -1);
    const int hub = 1;
    const auto a = g.vertices(width);
    const auto b = g.vertices(width);
    for (int j = 0; j < width; ++j) {
        g.add(g.s, a[j], C_MAX);
        g.add(b[j], hub, C_MAX);
    }
    for (int u : a) for (int v : b) g.add(u, v, (1LL << bits) - 1);
    std::vector<int> exits;
    int depth = 0;
    while ((1LL << depth) < 1LL * width * width) ++depth;
    for (int bit = bits - 1; bit >= 0; --bit) {
        int source = g.vertex(), sink = g.vertex();
        long long capacity = 1LL << bit;
        g.add(source, sink, capacity);
        for (int level = 0; level < depth; ++level) {
            const int next_source = g.vertex(), next_sink = g.vertex();
            g.add(next_source, source, capacity);
            g.add(next_source, sink, capacity);
            g.add(source, next_sink, capacity);
            g.add(sink, next_sink, capacity);
            source = next_source;
            sink = next_sink;
            capacity *= 2;
        }
        g.add(hub, source, 1LL * width * width * (1LL << bit));
        exits.push_back(sink);
    }
    g.t = g.vertex();
    for (int exit : exits) g.add(exit, g.t, C_MAX);
    assert(g.n == 3 + 2 * width + bits * (2 * depth + 2));
    assert(int(g.edges.size()) == 2 * width + width * width + bits * (4 * depth + 3));
    g.permute_vertices(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
