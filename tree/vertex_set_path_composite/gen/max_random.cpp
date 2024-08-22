#include <iostream>

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
    vector<int> perm = gen.perm<int>(n);
    for (int i = 1; i < n; i++) {
        int p = gen.uniform(0, i - 1);
        printf("%d %d\n", perm[p], perm[i]);
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
            int u = gen.uniform<int>(0, n - 1);
            int v = gen.uniform<int>(0, n - 1);
            int x = gen.uniform<int>(0, MOD - 1);
            printf("%d %d %d\n", u, v, x);
        }
    }
    return 0;
}
