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

long long pow(long long a,long long n,long long p){
  long long ret=1;
  for(;n>0;n>>=1,a=a*a%p)if(n%2==1)ret=ret*a%p;
  return ret;
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll up = gen.uniform((ll)9e8, P_MAX);
    vector<ll> primes = enum_prime(up - (ll)5e6, up);

    int t = T_MAX;
    printf("%d\n", t);
    for (int i = 0; i < t; i++) {
        ll p = primes[gen.uniform<ll>(0LL, primes.size() - 1)];
        ll k = gen.uniform(std::max(0LL,p - 1 - up), p - 1);
        ll y = pow(gen.uniform(0LL, p - 1), k, p);
        printf("%lld %lld %lld\n", k, y, p);
    }
    return 0;
}
