#include <cstdio>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_M_MAX;
    int m = N_AND_M_MAX;

    uint64_t val1 = seed == 0 ? 1ULL : gen.uniform(0ULL, ~0ULL);
    uint64_t val2 = seed == 0 ? 1ULL : gen.uniform(0ULL, ~0ULL);

    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        printf("%llu", val1);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < m; i++) {
        printf("%llu", val2);
        if (i != m - 1) printf(" ");
    }
    printf("\n");

    return 0;
}
