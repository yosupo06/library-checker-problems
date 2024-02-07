#include <iostream>
#include <cmath>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

template <class T, class U> T pow_mod(T x, U n, T md) {
    T r = 1 % md;
    x %= md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n <= a) break;
        ll t = d;
        ll y = pow_mod<__int128_t>(a, t, n);  // over
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = __int128_t(y) * y % n;  // flow
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}

ll generate_semiprime(ll s) {
    for (ll t = MAX_A / s; ; --t) {
        if (is_prime(t)) return s * t;
    }
}

int main(int, char* argv[]) {
    ll seed = atoll(argv[1]);
    auto gen = Random(seed);

    // 1 <= t/s <= 100
    ll gen_max = sqrt(MAX_A);
    ll gen_min = sqrt(MAX_A / 100);

    int q = MAX_Q;
    vector<ll> a(q);
    for (int i = 0; i < q; i++) {
        ll s;
        do {
            s = gen.uniform(gen_min, gen_max);
        } while(!is_prime(s));
        a[i] = generate_semiprime(s);
    }

    printf("%d\n", q);
    for (auto x: a) {
        printf("%lld\n", x);
    }
    return 0;
}
