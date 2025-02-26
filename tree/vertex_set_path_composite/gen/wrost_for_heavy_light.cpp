#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform<int>(1, MOD - 1);
        int b = gen.uniform<int>(0, MOD - 1);
        printf("%d %d\n", a, b);
    }

    constexpr int LG = 14;
    int leaf_begin = 2 << LG;
    int leaf_mid = 3 << LG;
    int leaf_end = 4 << LG;
    vector<int> top(leaf_end);
    iota(top.begin(), top.end(), 0);

    vector<pair<int, int>> edge;
    edge.reserve(n);
    for (int i = leaf_end; i < n; ++i) {
        int u = gen.uniform<int>(leaf_begin, leaf_end - 1) >>
                gen.uniform<int>(1, LG);
        edge.emplace_back(i, top[u]);
        top[u] = i;
    }
    for (int i = 1; i < leaf_end; ++i) {
        edge.emplace_back(top[i], i / 2);
    }

    vector<int> perm = gen.perm<int>(n - 1);
    for (int& element : perm) ++element;
    perm.insert(perm.begin(), 0);
    for (auto [u, v] : edge) {
        if (gen.uniform<int>(0, 1)) swap(u, v);
        printf("%d %d\n", perm[u], perm[v]);
    }

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        printf("%d ", t);
        if (t == 0) {
            int p = gen.uniform(0, n - 1);
            int c = gen.uniform<int>(1, MOD - 1);
            int d = gen.uniform<int>(0, MOD - 1);
            printf("%d %d %d\n", p, c, d);
        } else {
            int u = gen.uniform<int>(leaf_begin, leaf_mid - 1);
            int v = gen.uniform<int>(leaf_mid, leaf_end - 1);
            int x = gen.uniform<int>(0, MOD - 1);
            if (gen.uniform<int>(0, 1)) swap(u, v);
            printf("%d %d %d\n", perm[u], perm[v], x);
        }
    }
    return 0;
}
