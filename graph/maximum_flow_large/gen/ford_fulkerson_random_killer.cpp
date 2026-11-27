#include "../params.h"
#include "network.h"

// Weininger's Anti-Random-DFS construction (CC0), based on
// Dean-Goemans-Immorlica (2006): https://doi.org/10.1007/11841036_26
// https://codeforces.com/blog/entry/145343
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_random_dfs.cpp
// Replacing each priority choice with a chain makes random adjacency orders
// require 2^depth augmentations with probability (1 - 2^(-width))^(4*depth).
int main(int argc, char* argv[]) {
    Random rng(std::atoll(argv[1]));
    const int depth = argc > 3 ? std::atoi(argv[2]) : 29;
    const int width = argc > 3 ? std::atoi(argv[3]) : 56;
    assert(1 <= depth && depth <= 29 && width >= 1);
    Network g(3, 0, 2);
    int source = 1, sink = 2;
    g.add(source, sink, 1);
    for (int level = 0; level < depth; ++level) {
        const long long unit = 1LL << level;
        const auto a = g.vertices(width);
        const auto b = g.vertices(width);
        const auto c = g.vertices(width);
        const int x = g.vertex(), y = g.vertex();
        for (int j = 0; j < width; ++j) {
            if (j + 1 < width) {
                g.add(a[j], a[j + 1], 2 * unit);
                g.add(b[j], b[j + 1], 2 * unit);
                g.add(c[j], c[j + 1], 2 * unit);
            }
            g.add(a[j], x, unit);
            if (j == 0) g.add(y, b[j], unit);
            else g.add(b[j], y, unit);
            g.add(c[j], source, unit);
        }
        g.add(a.back(), sink, unit);
        g.add(sink, b.front(), unit);
        g.add(x, c.front(), unit);
        g.add(c.back(), y, unit);
        source = a.front();
        sink = b.back();
    }
    g.add(g.s, source, 1LL << depth);
    g.t = sink;
    assert(g.n == 3 + depth * (3 * width + 2));
    assert(int(g.edges.size()) == 2 + depth * (6 * width + 1));
    g.permute_vertices(rng);
    g.shuffle_edges(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
