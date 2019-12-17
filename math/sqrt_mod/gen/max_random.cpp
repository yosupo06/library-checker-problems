#include <iostream>
#include "random.h"

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

int main(int, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll up = gen.uniform(5'000'000, 1'000'000'000);
    vector<ll> primes = enum_prime(up - 5'000'000, up);
    vector<ll> small_primes = enum_prime(2, 1000);

    int t = 100'000;
    cout << t << "\n";
    for (int i = 0; i < t; i++) {
        ll p;
        if (gen.uniform_bool())
            p = primes[gen.uniform<ll>(0LL, primes.size() - 1)];
        else
            p = small_primes[gen.uniform<ll>(0LL, small_primes.size() - 1)];

        ll y = gen.uniform(0LL, p - 1);

        cout << y << " " << p << endl;
    }
    return 0;
}
