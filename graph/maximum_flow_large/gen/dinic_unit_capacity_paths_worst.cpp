#include "../params.h"
#include "network.h"

// maroonrk's comment: internally vertex-disjoint s-t paths of lengths 1..d.
// https://codeforces.com/blog/entry/52714 (comment by maroonrk)
// Unit edge capacities: d BFS phases, Theta(d^3) work for standard Dinic.
// https://cp-algorithms.com/graph/dinic.html#unit-capacities-networks
int main(int argc, char* argv[]) {
    // Optional d is used for structural checks and growth measurements.
    const int d = argc > 2 ? std::atoi(argv[2]) : 100;
    assert(d >= 1);
    Network g(2, 0, 1);
    for (int length = 1; length <= d; ++length) {
        int u = g.s;
        for (int step = 1; step < length; ++step) {
            const int v = g.vertex();
            g.add(u, v, 1);
            u = v;
        }
        g.add(u, g.t, 1);
    }
    assert(g.n == 2 + d * (d - 1) / 2);
    assert(int(g.edges.size()) == d * (d + 1) / 2);
    g.print(N_MAX, M_MAX, C_MAX);
}
