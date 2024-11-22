#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    auto sub = (seed <= 1) || ((seed - 2) & 1) ? 1000 : 10;
    auto div = (seed <= 1) || ((seed - 2) & 2) ? 1 : 2;

    int n = N_AND_M_MAX;
    int m = N_AND_M_MAX;
    vector<int> a(n), b(m);
    const int B = (seed <= 1) || ((seed - 2) & 4) ? 1<<15 : std::sqrt(MOD);
    for (int i = 0; i < n; i++) {
        int lw = gen.uniform(B - sub, B - 1);
        int up = gen.uniform(MOD / div / B - sub, MOD / div / B - 1);
        a[i] = up * B + lw;
    }
    for (int i = 0; i < m; i++) {
        int lw = gen.uniform(B - sub, B - 1);
        int up = gen.uniform(MOD / div / B - sub, MOD / div / B - 1);
        b[i] = up * B + lw;
    }

    printf("%d %d\n", n, m);

    for (int i = 0; i < n; i++) {
        printf("%d", a[i]);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d", b[i]);
        if (i != m - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
