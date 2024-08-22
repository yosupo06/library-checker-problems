#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    long long d = gen.uniform<int>(1, 1000);
    int trailing_zeros = gen.uniform<int>(1, d);
    long long k = gen.uniform<long long>(0, 1000);
    long long m = gen.uniform<long long>(1, 1000);

    printf("%lld %lld %lld\n", d, k, m);

    for (int i = 0; i < d; i++) {
        printf("%d", gen.uniform<int>(0, MOD - 1));
        printf(i == d - 1 ? "\n" : " ");
    }

    for (int i = 0; i < d; i++) {
        int c_i = 0;
        if (i + trailing_zeros < d) {
            c_i = gen.uniform<int>(0, MOD - 1);
        }
        printf("%d", c_i);
        printf(i == d - 1 ? "\n" : " ");
    }
    return 0;
}
