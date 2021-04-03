#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

struct E {
    int from, to, cost;
};

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_MAX - 100, N_MAX);
    int m = gen.uniform(n - 1, (int)min(N_MAX, (long long)n * (n - 1)));

    using P = pair<int, int>;
    set<P> used;
    vector<E> edges;
    auto add_edge = [&](int a, int b, int c) {
        if (used.count({a, b})) return false;
        used.insert({a, b});
        edges.push_back({a, b, c});
        return true;
    };
    for (int i = 1; i < n; i++) {
        add_edge(gen.uniform(0, i - 1), i, C_MAX);
    }
    for (int i = n - 1; i < m; i++) {
        int a, b;
        do {
            a = gen.uniform(0, n - 1);
            b = gen.uniform(0, n - 1);
        } while (a == b || used.count({a, b}));
        int c = gen.uniform(0LL, C_MAX);
        add_edge(a, b, c);
    }

    auto idx = gen.perm<int>(n);
    int s = idx[0];
    printf("%d %d %d\n", n, m, s);
    for (auto e: edges) {
        printf("%d %d %d\n", idx[e.from], idx[e.to], e.cost);
    }
    return 0;
}