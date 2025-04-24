#include <cstdio>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_M_MAX;
    int m = N_AND_M_MAX;

    int val1 = seed == 0 ? 1 : gen.uniform(0, MOD - 1);
    int val2 = seed == 0 ? 1 : gen.uniform(0, MOD - 1);

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%d", val1);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%d", val2);
        if (i != m - 1) printf(" ");
    }
    printf("\n");

    return 0;
}
