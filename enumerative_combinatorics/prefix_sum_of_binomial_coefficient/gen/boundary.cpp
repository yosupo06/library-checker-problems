#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    Random gen(seed);
    printf("%lld\n", T_MAX);
    for (int i = 0; i < T_MAX; ++i) {
        int n = gen.uniform<int>(0, N_MAX);
        int k;
        if (seed == 0) {
            int candidates[] = {0, std::min(1, n), n / 2,
                                std::max(0, (n - 1) / 2), std::max(0, n - 1), n};
            k = candidates[i % 6];
        } else {
            int candidates[] = {0, 1, 2, static_cast<int>(N_MAX - 2),
                                static_cast<int>(N_MAX - 1), static_cast<int>(N_MAX)};
            n = candidates[i % 6];
            k = gen.uniform(0, n);
        }
        printf("%d %d\n", n, k);
    }
}
