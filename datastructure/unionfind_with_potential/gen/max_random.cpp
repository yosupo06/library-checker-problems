#include <iostream>
#include "random.h"
#include "../sol/acl.h"
#include "../params.h"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

mint id() { return 0; }
mint op(const mint &a, const mint &b) { return a + b; }
mint inv(const mint &a) { return -a; }

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, N_MAX);
    int q = Q_MAX;

    vector<mint> A(n);
    for(mint &x : A)
        x = gen.uniform<int>(0, MOD - 1);

    printf("%d %d\n", n, q);
    for (int i = 0; i < q; i++) {
        int ty = gen.uniform_bool();
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        if (ty == 1) {
            printf("%d %d %d\n", ty, a, b);
        } else {
            mint x;
            if (gen.uniform_bool())
                x = gen.uniform<int>(0, MOD - 1);
            else
                x = op(inv(A[b]), A[a]);
            printf("%d %d %d %d\n", ty, a, b, x.val());
        }
    }
    return 0;
}
