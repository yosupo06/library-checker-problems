#include <iostream>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

/// g:gcd(a, b), ax+by=g
struct EG { ll g, x, y; };
EG ext_gcd(ll a, ll b) {
    if (b == 0) {
        if (a >= 0) return EG{a, 1, 0};
        else return EG{-a, -1, 0};
    } else {
        auto e = ext_gcd(b, a % b);
        return EG{e.g, e.y, e.x - a / b * e.y};
    }
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX / 2 * 2;

    printf("%d\n", n);
    for (int i = 0; i < n / 2; i++) {
        ll x = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        ll y = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        auto eg = ext_gcd(x, y);
        printf("%lld %lld\n", x, y);
        printf("%lld %lld\n", -eg.y, eg.x);
    }
    return 0;
}
