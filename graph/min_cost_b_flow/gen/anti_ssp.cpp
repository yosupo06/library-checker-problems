#include "common.h"

Graph gen_anti_ssp(const size_t k) {
    const Flow max_flow = 5 * ((Flow)(1) << (k-2)) - 2;
    const Flow inf = max_flow + 2;
    const size_t n = 2 * k + 2;
    Graph graph(n);
    graph.bs[0] += max_flow;
    graph.bs[n-1] -= max_flow;
    rep(i, k) {
        graph.add_edge(0, i + 1, 0, i == 0 ? 1 : i == 1 ? 3 : ((Flow)(5) << (i - 2)), 0);
    }
    graph.add_edge(1, k + 1, 0, inf, 0);
    rep(i, k) rep(j, k) if (i != j) {
        graph.add_edge(i+1, k+j+1, 0, inf, ((Flow)(1) << (std::max(i, j))) - 1);
    }
    rep(i, k) {
        graph.add_edge(i+1+k, 2*k+1, 0, i < 2 ? 2 : ((Flow)(5) << (i - 2)), 0);
    }
    return graph;
}

int main(const int, const char**) {
    using namespace std;
    size_t k = 3;
    Graph g = gen_anti_ssp(k);
    assert(g.satisfies_constraints());
    while (true) {
        ++k;
        Graph h = gen_anti_ssp(k);
        if (h.satisfies_constraints()) {
            g = h;
        } else {
            break;
        }
    }
    g.output();
    return 0;
}
