#include <cassert>
#include <cstdio>
#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    const int k = 12 + atoll(argv[1]);
    assert(12 <= k and k <= 16);

    auto genN = [&]{
        long long N = gen.uniform<long long>(0LL, MOD - 1);
        N |= (1LL << (k - 1)) - 1;
        N &= ~(1LL << k);
        return N;
    };

    int T = T_MAX;
    printf("%d\n", T);
    for (int t = 0; t < T; ++t) {
        long long N = genN();
        while (N >= MOD) N = genN();
        printf("%d\n", int(N));
    }
    return 0;
}
