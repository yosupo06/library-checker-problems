#include "random.h"
#include <iostream>
#include <vector>
#include <cassert>

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

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n <= a) break;
        long long t = d;
        long long y = pow_mod<__int128_t>(a, t, n);  // over
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


vector<ll> enum_prime(ll l, ll r) {
    vector<int> is_prime(r - l + 1, true);
    for (ll i = 2; i * i <= r; i++) {
        for (ll j = max(2 * i, (l + i - 1) / i * i); j <= r; j += i) {
            assert(l <= j && j <= r);
            is_prime[j - l] = false;
        }
    }
    vector<ll> res;
    for (ll i = l; i <= r; i++) {
        if (2 <= i && is_prime[i - l]) res.push_back(i);
    }
    return res;
}

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll up = gen.uniform((ll)1e4, (ll)2e4);
    vector<ll> primes = enum_prime(up - (ll)5e3, up);
    int t = 5000;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        ll k,p;
        bool find=false;
        while(!find) {
            for (long c=2;c<20;++c){
                k = primes[gen.uniform<ll>(0LL, primes.size() - 1)];
                p = c*k*k+1;
                if (is_prime(p) && p <= 1e9){
                    find=true;
                    break;
                }
            }
        }
        ll y = pow_mod<__int128_t>(gen.uniform(0LL, p - 1),k,p);
        printf("%lld %lld %lld\n", k, y, p);
    }
    return 0;
}
