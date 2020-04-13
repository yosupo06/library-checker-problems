#include "random.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "../params.h"

using namespace std;
using ll = long long;

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

bool is_prime(ll a) {
  for (ll div = 2; div*div <= a; ++div) {
    if (a % div == 0) return false;
  }
  return true;
}

// Suppose a is prime.
bool is_safeprime(ll a) {
  return a>=3 && is_prime((a-1)/2);
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int t = 100;
    printf("%d\n", t);

    ll up = gen.uniform((ll)9e8, (ll)1e9);
    vector<ll> primes = enum_prime((ll)up - (ll)5e6, up);
    for (int i = 0; i < t; i++) {
        ll p = 0;
        while (!is_safeprime(p)) p = primes[gen.uniform<ll>(0LL, primes.size() - 1)];
        ll y = gen.uniform(0LL, p - 1);
        ll x = gen.uniform(0LL, p - 1);
        printf("%lld %lld %lld\n", x, y, p);
    }
    return 0;
}
