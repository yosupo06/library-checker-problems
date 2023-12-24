#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long d = gen.uniform<int>(1, D_MAX);
    long long k = gen.uniform<long long>(0, K_MAX);
    long long m = gen.uniform<long long>(1, M_MAX);

    printf("%lld %lld %lld\n", d, k, m);

    for(int _ = 0; _ < 2; _++) {
        for (int i = 0; i < d; i++) {
            printf("%d", gen.uniform<int>(0, MOD - 1));
            printf(i == d - 1 ? "\n" : " ");
        }
    }
    return 0;
}
