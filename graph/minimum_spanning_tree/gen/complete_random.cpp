#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

struct E {
    int from, to, cost;
};

int main(int, char *argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = (1 << (5 + seed % 5));
    int m = n * (n - 1) / 2;

    vector<E> edges;
    for (int u = 1; u < n; u++) {
        for (int v = 0; v < u; v++) {
            int c = gen.uniform(0LL, C_MAX);
            edges.push_back({u, v, c});
        }
    }

    auto idx = gen.perm<int>(n);
    printf("%d %d\n", n, m);
    for (auto e : edges) {
        printf("%d %d %d\n", idx[e.from], idx[e.to], e.cost);
    }

    return 0;
}
