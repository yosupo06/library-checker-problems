#include <iostream>
#include "random.h"

using namespace std;
using ll = long long;

template<class T, class U>
T pow_mod(T x, U n, T md) {
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

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    vector<ll> primes;
    while (primes.size() <= 10000) {
        ll p = gen.uniform(2, 1'000'000'000);
        if (is_prime(p)) primes.push_back(p);
    }

    int t = gen.uniform(1, 100'000);
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        ll p = primes[gen.uniform<ll>(0LL, primes.size() - 1)];
        ll y = gen.uniform(0LL, p - 1);

        cout << y << " " << p << endl;
    }
    return 0;
}
