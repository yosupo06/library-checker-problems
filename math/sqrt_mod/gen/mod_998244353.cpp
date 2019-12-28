#include <iostream>
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100'000;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        ll p = 998244353;
        ll y = gen.uniform(0LL, p - 1);

        printf("%lld %lld\n", y, p);
    }
    return 0;
}
