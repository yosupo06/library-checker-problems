#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

// binary gcd
ll gcd(ll _a, ll _b) {
    ull a = abs(_a), b = abs(_b);
    if (a == 0) return b;
    if (b == 0) return a;
    int shift = bsf(a | b);
    a >>= bsf(a);
    do {
        b >>= bsf(b);
        if (a > b) swap(a, b);
        b -= a;
    } while (b);
    return (a << shift);
}

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

// return pair(factor, # of step)
pair<ll, ll> pollard_single(ll n) {
    auto f = [&](ll x) { return (__int128_t(x) * x + 1) % n; };
    if (is_prime(n)) return {n, 1};
    if (n % 2 == 0) return {2, 1};
    ll st = 0;
    ll step = 0;
    while (true) {
        st++;
        ll x = st, y = f(x);
        while (true) {
            step++;
            ll p = gcd((y - x + n), n);
            if (p == 0 || p == n) break;
            if (p != 1) return {p, step};
            x = f(x);
            y = f(f(y));
        }
    }
}

// return step
ll pollard(ll n) {
    if (n == 1) return 1;
    auto x = pollard_single(n);
    if (x.first == n) return x.second;
    return pollard(x.first) + pollard(n / x.first) + x.second;
}

vector<long long> enum_prime(long long st, long long ed) {
    if (st == 1) st = 2;
    vector<bool> is_prime(ed - st + 1, true);
    for (long long i = 2; i * i <= ed; i++) {
        for (long long j = (st + i - 1) / i * i; j <= ed; j += i) {
            is_prime[j - st] = false;
        }
    }
    vector<long long> primes;
    for (long long i = st; i <= ed; i++) {
        if (is_prime[i - st]) primes.push_back(i);
    }
    return primes;
}

int main(int, char* argv[]) {


    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    auto primes = enum_prime(1'000'000'000 - 1'000'000, 1'000'000'000);
    int k = int(primes.size());
    int q = MAX_Q;
    vector<pair<long long, long long>> a;
    for (int i = 0; i < 20 * q; i++) {
        long long x = primes[gen.uniform(0, k - 1)] * primes[gen.uniform(0, k - 1)];
        a.push_back({pollard(x), x});
    }
    sort(a.begin(), a.end(), greater<>());
    a.resize(q);

    printf("%d\n", q);
    for (auto x: a) {
        printf("%lld\n", x.second);
    }
    return 0;
}
