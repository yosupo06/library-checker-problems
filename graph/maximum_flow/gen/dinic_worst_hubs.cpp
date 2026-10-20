#include "../params.h"
#include "network.h"

// MiSawa (2021), Dinic worst case behavior: four-hub Zadeh/TopCoder variant.
// https://gist.github.com/MiSawa/8016ff5023c2c43d7416fdd426bdd9f7
// Independently constructed. C_MAX replaces the original unbounded rail capacity.
// N = 4*p + 2*k + 6, M = k*k + 4*k + 6*p + 2, F = k*k*(p+1).
int main(int argc, char* argv[]) {
    const int k = argc > 3 ? std::atoi(argv[2]) : 75;
    const int p = argc > 3 ? std::atoi(argv[3]) : 36;
    assert(k >= 1 && p >= 0 && 1LL * k * k * (p + 1) <= C_MAX);
    Network g(2, 0, 1);
    auto source = g.vertices(2 * p), sink = g.vertices(2 * p);
    source.insert(source.begin(), g.s);
    sink.insert(sink.begin(), g.t);
    const auto a = g.vertices(k), b = g.vertices(k);
    const int in_a = g.vertex(), out_a = g.vertex();
    const int in_b = g.vertex(), out_b = g.vertex();
    for (int v : a) { g.add(in_a, v, C_MAX); g.add(v, out_a, C_MAX); }
    for (int v : b) { g.add(in_b, v, C_MAX); g.add(v, out_b, C_MAX); }
    for (int u : a) for (int v : b) g.add(u, v, 1);
    for (int i = 0; i < 2 * p; ++i) {
        g.add(source[i], source[i + 1], C_MAX);
        g.add(sink[i + 1], sink[i], C_MAX);
    }
    for (int i = 0; i <= 2 * p; i += 2) {
        g.add(source[i], i % 4 == 0 ? in_a : in_b, k * k);
        g.add(i % 4 == 0 ? out_b : out_a, sink[i], k * k);
    }
    assert(g.n == 4 * p + 2 * k + 6);
    assert(int(g.edges.size()) == k * k + 4 * k + 6 * p + 2);
    g.print(N_MAX, M_MAX, C_MAX);
}
