#include <iostream>
#include <set>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int l = gen.uniform(1, 100'000);
    int r = gen.uniform(1, 100'000);
    int m = gen.uniform(1, 200'000);

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