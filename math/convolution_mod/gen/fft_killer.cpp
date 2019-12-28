#include <cstdio>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 1 << 19;
    int m = 1 << 19;
    vector<int> a(n), b(m);
    constexpr int MOD = 998244353;
    constexpr int B = 1<<15;
    for (int i = 0; i < n; i++) {
        int lw = gen.uniform(B - 1000, B - 1);
        int up = gen.uniform(MOD / B - 1000, MOD / B - 1);
        a[i] = up * B + lw;
    }
    for (int i = 0; i < m; i++) {
        int lw = gen.uniform(B - 1000, B - 1);
        int up = gen.uniform(MOD / B - 1000, MOD / B - 1);
        b[i] = up * B + lw;
    }

    printf("%d %d\n", n, m);

    for (int i = 0; i < n; i++) {
        printf("%d\n", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d\n", b[i]);
        if (i != m - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
