#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long n = 65535 + gen.uniform<int>(0, 2);
    long long k = gen.uniform<long long>(0, K_MAX);

    printf("%lld %lld\n", n, k);

    for(int _ = 0; _ < 2; _++) {
        for (int i = 0; i < n; i++) {
            printf("%d", gen.uniform<int>(0, MOD - 1));
            printf(i == n - 1 ? "\n" : " ");
        }
    }
    return 0;
}
