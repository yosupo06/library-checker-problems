#include <iostream>
#include <set>
#include "random.h"
#include "../params.h"
using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int l = 0, r = 0, m = 0;

    using P = pair<int, int>;
    vector<P> edges;
    while (l < L_MAX - 100 && r < R_MAX - 100 && m < M_MAX - 100) {
        int nl = gen.uniform(1, 20);
        int nr = gen.uniform(1, 20);
        int nm = gen.uniform(1, min(nl * nr, 100));
        set<P> ns;
        while (int(ns.size()) < nm) {
            int u = gen.uniform(l, l + nl - 1);
            int v = gen.uniform(r, r + nr - 1);
            ns.insert({u, v});
        }
        for (auto p: ns) edges.push_back(p);

        l += nl;
        r += nr;
        m += nm;
    }

    m = int(edges.size());

    printf("%d %d %d\n", l, r, m);
    for (auto edge: edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}