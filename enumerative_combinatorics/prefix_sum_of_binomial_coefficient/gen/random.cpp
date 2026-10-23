#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    Random gen(seed);
    printf("%lld\n", T_MAX);
    for (int i = 0; i < T_MAX; ++i) {
        int n = gen.uniform<int>(seed == 1 ? N_MAX / 2 : 0, N_MAX);
        int k = gen.uniform(0, n);
        if (seed == 2) k = gen.uniform(n / 3, n * 2 / 3);
        printf("%d %d\n", n, k);
    }
}
