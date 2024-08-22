#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll n = 1'000'000;
    ll m = gen.uniform(1LL, 1'000'000'000LL);
    printf("%lld %lld\n", n, m);
    return 0;
}
