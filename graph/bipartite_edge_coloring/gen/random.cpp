#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int l = gen.uniform<int>(1, L_MAX);
    int r = gen.uniform<int>(1, R_MAX);
    int m = gen.uniform<int>(1, M_MAX);

    using P = pair<int, int>;
    set<P> edges;
    for (int ph = 0; ph < m; ph++) {
        int u = gen.uniform(0, l - 1);
        int v = gen.uniform(0, r - 1);
        edges.insert({u, v});
    }
    m = int(edges.size());

    printf("%d %d %d\n", l, r, m);
    for (auto edge: edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}