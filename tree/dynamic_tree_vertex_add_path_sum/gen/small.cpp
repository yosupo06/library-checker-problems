#include "random.h"
#include "toptree.hpp"
#include "../params.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(0, 1000);
    int q = gen.uniform(0, 1000);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%lld", gen.uniform(A_AND_X_MIN, A_AND_X_MAX));
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    vector<int> u(n - 1), v(n - 1);
    for (int i = 0; i < n - 1; i++) {
        u[i] = gen.uniform(0, i);
        v[i] = i + 1;
    }

    {
        auto perm = gen.perm<int>(n);
        for (int i = 0; i < n - 1; i++) {
            u[i] = perm[u[i]];
            v[i] = perm[v[i]];
        }
    }

    dynamic_tree tree(n);

    for (int i = 0; i < n - 1; i++) {
        printf("%d %d\n", u[i], v[i]);
        tree.link(u[i], v[i]);
    }

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        printf("%d ", t);
        if(t == 0) {
          int eidx = gen.uniform(0, n - 2);
          auto p = tree.cut(eidx);
          int u = p.first;
          int v = p.second;
          int w = tree.random_vertex(gen, u);
          int x = tree.random_vertex(gen, v);
          tree.link(w, x);
          printf("%d %d %d %d\n", u, v, w, x);
        }
        else if (t == 1) {
            int p = gen.uniform(0, n - 1);
            int x = gen.uniform(A_AND_X_MIN, A_AND_X_MAX);
            printf("%d %d\n", p, x);
        } else {
            auto u = gen.uniform(0, n - 1);
            auto v = gen.uniform(0, n - 1);
            printf("%d %d\n", u, v);
        }
    }
    return 0;
}
