#pragma once

#include <array>
#include <limits>

#include "network.h"

// Independent implementations of the constructions in Weininger's article,
// based on Cheriyan-Maheshwari and Cherkassky-Goldberg. The Anti-FIFO/HLPP/
// scaling reference files explicitly carry CC0; AK has no explicit license,
// so only its graph structure is used here, not its source code.
// https://codeforces.com/blog/entry/145343
// https://github.com/leonard-weininger/worst-case-max-flow/tree/main/generators

// Weininger, Anti-FIFO (CC0), inspired by Cheriyan-Maheshwari (1989).
// https://doi.org/10.1137/0218072
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_fifopp.cpp
inline Network anti_fifo_network(int k, long long infinity) {
    Network g(1, 0, -1);
    std::vector<int> a(k), b(k);
    for (int i = 0; i < k; ++i) { a[i] = g.vertex(); b[i] = g.vertex(); }
    const int p = g.vertex(), q = g.vertex();
    auto line = g.vertices(8 * k - 3);
    std::reverse(line.begin(), line.end());
    g.t = line[0];
    for (int i = 0; i < k; ++i) g.add(a[i], b[i], i + 1 == k ? infinity : 1);
    g.add(g.s, p, infinity);
    for (int i = 0; i < k; ++i) { g.add(p, a[i], infinity); g.add(b[i], q, infinity); }
    for (int i = int(line.size()) - 1; i > 0; --i) g.add(line[i], line[i - 1], infinity);
    for (int i = 0; i < k; ++i) { g.add(q, line[8 * i], k); g.add(p, line[8 * i + 4], k); }
    assert(g.n == 10 * k && int(g.edges.size()) == 13 * k - 3);
    assert(2LL * k * k <= infinity);
    return g;
}

inline std::array<int, 3> hlpp_parameters(int max_n, int max_m, long long max_c) {
    std::array<int, 3> best = {1, 1, 1};
    long long score = 0;
    for (int k = 1; 10 + 8 + 2 * (2 * k + 3) <= max_n; ++k) {
        for (int w = 1; w * w <= max_m; ++w) {
            const int l = int(std::min({
                (max_n - 10LL - 2LL * w * (2 * k + 3)) / 8,
                (max_m - 2LL - 2LL * w * (2 * k + 5) - 1LL * w * w) / 18,
                max_c / (2LL * w * w + 4)}));
            if (l < 1) continue;
            const long long estimate = 2LL * l * w * w * k;
            if (estimate > score) { score = estimate; best = {k, w, l}; }
        }
    }
    return best;
}

// Weininger, Anti-HLPP (CC0), inspired by Cheriyan-Maheshwari (1989).
// https://doi.org/10.1137/0218072
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_hlpp.cpp
inline Network anti_hlpp_network(int k, int w, int l) {
    const long long infinity = 2LL * l * w * w + 4LL * l;
    Network g(1, 0, -1);
    const int a[2] = {g.vertex(), g.vertex()};
    const int b[2] = {g.vertex(), g.vertex()};
    const int p[2] = {g.vertex(), g.vertex()};
    const int q[2] = {g.vertex(), g.vertex()};
    std::array<std::vector<int>, 2> side, middle;
    for (int h = 0; h < 2; ++h) {
        side[h] = g.vertices(w * (k + 3));
        middle[h] = g.vertices(w * k);
    }
    const auto auxiliary = g.vertices(2 * l);
    auto line = g.vertices(6 * l + 1);
    std::reverse(line.begin(), line.end());
    g.t = line[0];
    // Earlier arcs get priority in the canonical adjacency order.
    for (int i = 0; i < 2 * l; ++i) {
        const int h = 1 - i % 2;
        g.add(g.s, auxiliary[i], infinity);
        g.add(auxiliary[i], line[0], 1);
        g.add(auxiliary[i], a[h], w * w);
        g.add(auxiliary[i], b[h], 1);
    }
    for (int j = 0; j < w; ++j) {
        for (int h = 0; h < 2; ++h) g.add(a[h], side[h][j], w);
    }
    for (int row = 0; row < k + 2; ++row) {
        for (int j = 0; j < w; ++j) {
            for (int h = 0; h < 2; ++h) g.add(side[h][row * w + j], side[h][(row + 1) * w + j], w);
        }
    }
    for (int j = 0; j < w; ++j) {
        for (int h = 0; h < 2; ++h) g.add(side[h][(k + 2) * w + j], b[h], w);
    }
    for (int i = 0; i < l; ++i) {
        g.add(b[0], line[6 * i], 1);
        g.add(b[1], line[6 * i + 3], 1);
    }
    for (int h = 0; h < 2; ++h) g.add(a[h], p[h], infinity);
    for (int j = 0; j < w; ++j) {
        for (int h = 0; h < 2; ++h) g.add(p[h], middle[h][j], infinity);
    }
    for (int row = 0; row + 1 < k; ++row) {
        for (int j = 0; j < w; ++j) {
            for (int h = 0; h < 2; ++h) g.add(middle[h][row * w + j], middle[h][(row + 1) * w + j], infinity);
        }
    }
    for (int j = 0; j < w; ++j) {
        for (int h = 0; h < 2; ++h) g.add(middle[h][(k - 1) * w + j], q[h], infinity);
    }
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < w; ++j) g.add(middle[0][i], middle[1][j], 1);
    }
    for (int i = 0; i < l; ++i) {
        g.add(q[0], line[6 * i + 6], w * w);
        g.add(q[1], line[6 * i + 3], w * w);
    }
    for (int i = 6 * l; i > 0; --i) g.add(line[i], line[i - 1], infinity);
    assert(g.n == 10 + 8 * l + 2 * w * (2 * k + 3));
    assert(int(g.edges.size()) == 18 * l + 2 * w * (2 * k + 5) + w * w + 2);
    return g;
}

// Cherkassky-Goldberg AK topology (1994 generator; discussed in 1997 paper).
// Independently constructed; the reference source has no explicit license.
// https://doi.org/10.1007/PL00009180
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/ak.cpp
inline Network ak_network(int size, long long infinity) {
    Network g(1, 0, -1);
    const auto first = g.vertices(size + 1);
    const auto tail = g.vertices(size + 1);
    const auto second = g.vertices(2 * size + 2);
    g.t = g.vertex();
    for (int i = 0; i < size; ++i) {
        g.add(first[i], first[i + 1], size - i + 1);
        g.add(first[i], tail[0], 1);
    }
    g.add(first[size], tail[size], 1);
    g.add(first[size], tail[0], 1);
    for (int i = 0; i < size; ++i) g.add(tail[i], tail[i + 1], size + 1);
    for (int i = 0; i < 2 * size + 1; ++i) g.add(second[i], second[i + 1], size);
    for (int i = 0; i < size; ++i) g.add(second[i], second[2 * size + 1 - i], 1);
    g.add(g.s, first[0], infinity);
    g.add(g.s, second[0], infinity);
    g.add(tail.back(), g.t, infinity);
    g.add(second.back(), g.t, infinity);
    assert(g.n == 4 * size + 6 && int(g.edges.size()) == 6 * size + 7);
    return g;
}

// Washington generator, function 2 (RLevel): three DISTINCT random neighbors
// in the next column, and terminal capacities 3*range. This is the original
// structure, with repository RNG replacing its platform-dependent RNG.
// https://archive.dimacs.rutgers.edu/pub/netflow/generators/network/washington/
inline Network washington_network(int rows, int columns, long long range, Random& rng) {
    assert(rows >= 3 && columns >= 2);
    Network g(rows * columns + 2, 0, rows * columns + 1);
    for (int i = 0; i < rows; ++i) {
        g.add(g.s, 1 + i, 3 * range);
        g.add(1 + (columns - 1) * rows + i, g.t, 3 * range);
    }
    for (int column = 0; column + 1 < columns; ++column) {
        for (int i = 0; i < rows; ++i) {
            auto neighbors = rng.choice(3, 0, rows - 1);
            rng.shuffle(neighbors.begin(), neighbors.end());
            for (int j : neighbors) {
                g.add(1 + column * rows + i, 1 + (column + 1) * rows + j, rng.uniform(1LL, range));
            }
        }
    }
    assert(g.n == rows * columns + 2);
    assert(int(g.edges.size()) == rows * (3 * columns - 1));
    return g;
}

// Nested threshold gadgets, adapted to the hub-based Zadeh construction.
// Based on Weininger's Anti-Scaling-Dinic construction (CC0):
// https://codeforces.com/blog/entry/145343
// https://github.com/leonard-weininger/worst-case-max-flow/blob/9d1c94b32cb38c6116a8e1d5a42038a2ba320496/generators/gen_anti_scaling_dinic.cpp
// Every threshold offers w^2 units, each of size 2^bit; subsequent thresholds
// attach at the far ends of the preceding rails. F = w^2 * (2^bits - 1).
inline Network anti_scaling_network(int k, int rounds, int bits, int w,
                                     long long infinity) {
    assert(k * k * rounds >= w * w);
    assert(1LL * w * w * ((1LL << bits) - 1) <= infinity);
    Network g(3, 0, 1);
    int entrance = 2, exit = 1;
    const auto a = g.vertices(w), b = g.vertices(w);
    for (int j = 0; j < w; ++j) { g.add(g.s, a[j], infinity); g.add(b[j], entrance, infinity); }
    for (int u : a) for (int v : b) g.add(u, v, (1LL << bits) - 1);
    for (int bit = bits - 1; bit >= 0; --bit) {
        Network gadget = zadeh_network(k, rounds);
        const int offset = g.n;
        g.n += gadget.n;
        const long long unit = 1LL << bit;
        const int rail_length = 4 * (rounds - 1) + 1;
        const int p = 2 * rail_length, q = p + rounds;
        long long remaining = w * w;
        std::vector<long long> stage(rounds);
        for (auto& cap : stage) { cap = std::min(1LL * k * k, remaining); remaining -= cap; }
        for (auto e : gadget.edges) {
            long long cap = e.c * unit;
            if (e.u < 2 * rail_length && e.v < 2 * rail_length) cap = infinity;
            if (p <= e.v && e.v < q) cap = stage[e.v - p] * unit;
            if (q <= e.u && e.u < q + rounds) cap = stage[e.u - q] * unit;
            if (p <= e.u && e.u < q) cap = stage[e.u - p] * unit;
            if (q <= e.v && e.v < q + rounds) cap = stage[e.v - q] * unit;
            g.add(offset + e.u, offset + e.v, cap);
        }
        g.add(entrance, offset + gadget.s, infinity);
        g.add(offset + gadget.t, exit, infinity);
        entrance = offset + rail_length - 1;
        exit = offset + 2 * rail_length - 1;
    }
    assert(g.n == 3 + 2 * w + bits * (10 * rounds + 2 * k - 4));
    assert(int(g.edges.size()) == 2 * w + w * w + bits * (12 * rounds + k * k + 2 * k - 6));
    return g;
}
