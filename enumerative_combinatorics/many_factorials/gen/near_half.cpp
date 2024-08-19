#include <cstdio>
#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int T = T_MAX;
    printf("%d\n", T);
    for (int t = 0; t < T; ++t) {
        int N = gen.uniform<int>(0.45 * MOD, 0.55 * MOD);
        printf("%d\n", N);
    }
    return 0;
}
