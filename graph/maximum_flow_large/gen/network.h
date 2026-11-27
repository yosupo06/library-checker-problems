#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>

#include "random.h"

struct Network {
    struct Edge { int u, v; long long c; };
    int n, s, t;
    std::vector<Edge> edges;
    Network(int n_, int s_, int t_) : n(n_), s(s_), t(t_) {}
    int vertex() { return n++; }
    std::vector<int> vertices(int size) {
        std::vector<int> result;
        for (int i = 0; i < size; ++i) result.push_back(vertex());
        return result;
    }
    void add(int u, int v, long long c) { edges.push_back({u, v, c}); }
    void permute_vertices(Random& rng) {
        const auto p = rng.perm<int>(n);
        s = p[s];
        t = p[t];
        for (auto& e : edges) { e.u = p[e.u]; e.v = p[e.v]; }
    }
    void shuffle_edges(Random& rng) { rng.shuffle(edges.begin(), edges.end()); }
    void print(int max_n, int max_m, long long max_c) const {
        assert(2 <= n && n <= max_n && s != t);
        assert(0 <= s && s < n && 0 <= t && t < n);
        assert(int(edges.size()) <= max_m);
        printf("%d %d %d %d\n", n, int(edges.size()), s, t);
        for (const auto& e : edges) {
            assert(0 <= e.u && e.u < n && 0 <= e.v && e.v < n);
            assert(0 <= e.c && e.c <= max_c);
            printf("%d %d %lld\n", e.u, e.v, e.c);
        }
    }
};

inline long long mixed_capacity(Random& rng, long long max_c) {
    switch (rng.uniform(0, 3)) {
        case 0: return rng.uniform(0LL, max_c);
        case 1: return rng.uniform(0, 2);
        case 2: return max_c;
        default: {
            const long long p = 1LL << rng.uniform(0, 29);
            return std::min(max_c, p + rng.uniform(-1, 1));
        }
    }
}

inline Network random_network(int seed, int max_n, int max_m, long long max_c,
                              Random& rng) {
    const int n = seed < 2 ? 8 + seed : (seed < 4 ? max_n / 3 : max_n);
    const int m = seed < 2 ? 40 + seed : max_m;
    Network g(n, 0, n - 1);
    for (int i = 0; i < m; ++i) {
        const long long c = mixed_capacity(rng, max_c);
        const int v = rng.uniform(0, n - 1);
        const int u = rng.uniform(0, n - 1);
        g.add(u, v, c);
    }
    g.permute_vertices(rng);
    return g;
}

inline Network boundary_network(int seed, int max_n, int max_m, long long max_c,
                                Random& rng) {
    if (seed == 0) return Network(2, 1, 0);
    if (seed == 1) {
        Network g(7, 5, 2);
        // Loops at s, t and an intermediate vertex, plus an independent cycle.
        g.edges = {{5,5,max_c},{2,2,max_c},{1,1,max_c},
                   {5,1,3},{5,1,4},{1,5,2},{1,2,5},{2,5,max_c},
                   {3,5,8},{2,4,8},{1,3,6},{3,1,6},{5,2,0}};
        return g;
    }
    Network g(max_n, max_n - 2, max_n - 1);
    for (int i = 0; i < max_m; ++i) {
        // seed 2: excess must be returned from a large component; t isolated.
        const int bound = seed == 2 ? max_n - 2 : max_n - 1;
        int u = i < max_n - 1 ? g.s : rng.uniform(0, bound);
        int v = i < max_n - 1 ? i : rng.uniform(0, bound);
        g.add(u, v, seed == 3 ? 0 : max_c);
    }
    g.permute_vertices(rng);
    return g;
}

inline Network parallel_network(int seed, int max_n, int max_m, long long max_c,
                                Random& rng) {
    Network g(max_n, max_n - 2, max_n / 2);
    for (int i = 0; i < max_m; ++i) {
        if (seed == 0) g.add(g.s, g.t, max_c);
        else if (seed == 1) {
            const int v = i / 2 % (max_n / 2);
            if (i % 2 == 0) g.add(g.s, v, max_c);
            else g.add(v, g.t, max_c);
        } else {
            const int u[] = {g.s, g.t, g.s, g.s, g.t};
            const int v[] = {g.t, g.s, g.s, g.t, g.t};
            g.add(u[i % 5], v[i % 5], i % 5 == 3 ? 0 : max_c);
        }
    }
    g.permute_vertices(rng);
    g.shuffle_edges(rng);
    return g;
}

inline Network layered_network(int seed, int max_n, int max_m, long long max_c,
                               Random& rng) {
    Network g(max_n, 0, max_n - 1);
    if (seed == 0) {
        for (int i = 0; i + 1 < max_n; ++i) g.add(i, i + 1, max_c);
        for (int i = 1; i < max_n; ++i) g.add(i, i - 1, i == max_n / 2 ? 0 : 1);
    } else if (seed == 1) {
        // Many long routes reach a single final bottleneck.
        for (int i = 0; i + 1 < max_n; ++i) g.add(i, i + 1, max_c);
        g.edges.back().c = 1;
        while (int(g.edges.size()) < max_m) {
            const int u = rng.uniform(0, max_n - 3);
            const int v = rng.uniform(u + 1, max_n - 2);
            g.add(u, v, mixed_capacity(rng, max_c));
        }
    } else {
        const int width = std::min(30, max_n / 5);
        for (int j = 1; j <= width; ++j) g.add(0, j, max_c);
        for (int u = 1; u + width < max_n - 1; ++u) g.add(u, u + width, max_c);
        for (int u = max_n - 1 - width; u < max_n - 1; ++u) g.add(u, max_n - 1, 1);
        while (int(g.edges.size()) < max_m) {
            const int u = rng.uniform(1, max_n - 2);
            const long long c = rng.uniform(0, 2);
            const int v = std::min(max_n - 2, u + rng.uniform(0, width));
            g.add(u, v, c);
        }
    }
    g.permute_vertices(rng);
    if (seed != 0) g.shuffle_edges(rng);
    return g;
}

// MiSawa: https://gist.github.com/MiSawa/47b1d99c372daffb6891662db1a2b686
// Independently construct the two-vertex branching layers, preserving input
// order. Vertex 99 is intentionally unused in the original 100/192 instance.
inline Network misawa_network(int n = 100) {
    assert(n >= 8 && n % 2 == 0);
    Network g(n, 0, 4);
    g.edges = {{0,1,1},{0,2,2},{2,1,2},{3,4,2},{1,5,3},{1,6,3}};
    int last = 5;
    for (int next = 7; next + 1 < n; next += 2) {
        for (int u = last; u <= last + 1; ++u) {
            for (int v = next; v <= next + 1; ++v) g.add(u, v, 3);
        }
        last = next;
    }
    g.add(last, 3, 3);
    g.add(last + 1, 3, 3);
    assert(int(g.edges.size()) == 2 * n - 8);
    return g;
}

// Zadeh-style alternating residual bipartite gadget, independently constructed
// with shared hubs. Central arcs retain capacity ONE. F = rounds * k^2.
// Zadeh (1972); see Weininger's Anti-Shortest-Paths construction and discussion:
// https://doi.org/10.1145/321679.321693
// https://codeforces.com/blog/entry/145343
// This hub variant has N = 10*rounds + 2*k - 4, M = 12*rounds + k*k + 2*k - 8.
inline Network zadeh_network(int k, int rounds) {
    assert(k >= 2 && rounds >= 1);
    const int length = 4 * (rounds - 1) + 1;
    const int p = 2 * length, q = p + rounds;
    const int left = q + rounds, right = left + 1;
    const int a = right + 1, b = a + k;
    Network g(b + k, 0, length);
    const long long total = 1LL * rounds * k * k;
    for (int i = 0; i + 1 < length; ++i) {
        g.add(i, i + 1, total);
        g.add(length + i + 1, length + i, total);
    }
    for (int i = 0; i < rounds; ++i) {
        g.add(4 * i, p + i, k * k);
        g.add(q + i, length + 4 * i, k * k);
        g.add(p + i, i % 2 == 0 ? left : right, k * k);
        g.add(i % 2 == 0 ? right : left, q + i, k * k);
    }
    for (int j = 0; j < k; ++j) g.add(left, a + j, k);
    for (int j = 0; j < k; ++j) g.add(b + j, right, k);
    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) g.add(a + i, b + j, 1);
    }
    assert(g.n == 10 * rounds + 2 * k - 4);
    assert(int(g.edges.size()) == 12 * rounds + k * k + 2 * k - 8);
    return g;
}

// Bidirectional Genrmf variant described by Weininger (Goldfarb-Grigoriadis).
// Each direction between frames has its OWN uniform permutation. Terminals
// are the first corner of frame 0 and last corner of frame b-1.
// https://github.com/leonard-weininger/worst-case-max-flow/blob/main/generators/genrmf.cpp
// Goldfarb-Grigoriadis (1988): https://doi.org/10.1007/BF02288321
// Forward-only original: https://archive.dimacs.rutgers.edu/pub/netflow/generators/network/genrmf/
inline Network genrmf_network(int a, int b, Random& rng, bool backward = true) {
    assert(a >= 2 && b >= 2);
    const int frame = a * a;
    Network g(frame * b, 0, frame * b - 1);
    const long long grid_capacity = 1000LL * frame;
    for (int z = 0; z < b; ++z) {
        for (int x = 0; x < a; ++x) {
            for (int y = 0; y < a; ++y) {
                const int u = z * frame + x * a + y;
                if (x + 1 < a) { g.add(u, u + a, grid_capacity); g.add(u + a, u, grid_capacity); }
                if (y + 1 < a) { g.add(u, u + 1, grid_capacity); g.add(u + 1, u, grid_capacity); }
            }
        }
    }
    for (int z = 0; z + 1 < b; ++z) {
        for (int direction = 0; direction < (backward ? 2 : 1); ++direction) {
            const auto p = rng.perm<int>(frame);
            std::vector<bool> seen(frame, false);
            for (int i = 0; i < frame; ++i) {
                assert(!seen[p[i]]);
                seen[p[i]] = true;
                const int u = (z + direction) * frame + i;
                const int v = (z + 1 - direction) * frame + p[i];
                g.add(u, v, rng.uniform(1, 1000));
            }
        }
    }
    assert(g.n == a * a * b);
    assert(int(g.edges.size()) == 4 * a * (a - 1) * b + (backward ? 2 : 1) * a * a * (b - 1));
    return g;
}
