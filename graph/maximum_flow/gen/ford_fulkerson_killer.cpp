#include "../params.h"
#include "network.h"
#include <tuple>

// Dean-Goemans-Immorlica recursive DFS obstruction, with the edge-order
// adaptation discussed by lotusblume in CF 136682. Independently constructed.
// https://codeforces.com/blog/entry/136682#comment-1206553
// https://doi.org/10.1007/11841036_26
// Descending input order selects the expensive DFS priority. Reverse arcs
// are inserted alongside input arcs by the tested DFS implementation.
int main(int argc, char* argv[]) {
    const int k = argc > 2 ? std::atoi(argv[2]) : 28;
    assert(1 <= k && k <= 28);
    const int n = 6 * k + 4;
    Network g(n, 0, n - 1);
    int auxiliary = 4 * k, terminal = 6 * k + 2;
    int source = terminal--, sink = terminal--;
    g.add(source, sink, 2);
    for (int depth = 1; depth <= k; ++depth) {
        int new_source = terminal--, new_sink = terminal--;
        long long capacity = 1LL << depth;
        int a = auxiliary--, b = auxiliary--, c = auxiliary--, d = auxiliary--;
        g.add(new_source, a, capacity); g.add(a, source, capacity);
        g.add(new_source, b, capacity); g.add(b, sink, capacity);
        g.add(source, c, capacity); g.add(c, new_sink, capacity);
        g.add(sink, d, capacity); g.add(d, new_sink, capacity);
        source = new_source; sink = new_sink;
    }
    g.add(g.s, source, C_MAX); g.add(sink, g.t, C_MAX);
    const auto original = g.edges;
    for (auto e : original) g.add(e.v, e.u, 1);
    std::stable_sort(g.edges.begin(), g.edges.end(), [](const auto& a, const auto& b) {
        return std::tie(a.u, a.v) < std::tie(b.u, b.v);
    });
    std::reverse(g.edges.begin(), g.edges.end());
    g.print(N_MAX, M_MAX, C_MAX);
}
