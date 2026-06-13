#pragma once

#include <algorithm>
#include <cassert>
#include <cstdio>
#include <numeric>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;
using Poly = vector<ll>;

const vector<int> PRIME_CANDIDATES = {2, 3, 5, 7, 11, 101, 1013, 10133, 101333,1013377, 10133771, 101337727, 998244341, 998244353};

ll norm(ll x, ll p) {
    x %= p;
    if (x < 0) x += p;
    return x;
}

ll mod_pow(ll a, ll e, ll p) {
    ll r = 1 % p;
    while (e) {
        if (e & 1) r = r * a % p;
        a = a * a % p;
        e >>= 1;
    }
    return r;
}

ll mod_inv(ll a, ll p) { return mod_pow(a, p - 2, p); }

void trim(Poly& a) {
    while (!a.empty() && a.back() == 0) a.pop_back();
}

int deg(Poly a) {
    trim(a);
    return (int)a.size() - 1;
}

Poly sub(Poly a, const Poly& b, ll p) {
    if (a.size() < b.size()) a.resize(b.size());
    for (int i = 0; i < (int)b.size(); i++) a[i] = norm(a[i] - b[i], p);
    trim(a);
    return a;
}

Poly mul(const Poly& a, const Poly& b, ll p) {
    if (a.empty() || b.empty()) return {};
    Poly c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            c[i + j] = (c[i + j] + a[i] * b[j]) % p;
        }
    }
    trim(c);
    return c;
}

pair<Poly, Poly> divmod_poly(Poly a, Poly b, ll p) {
    trim(a);
    trim(b);
    int n = (int)a.size() - 1, m = (int)b.size() - 1;
    if (n < m) return {{}, a};
    Poly q(n - m + 1);
    ll inv = mod_inv(b.back(), p);
    for (int i = n; i >= m; i--) {
        ll coef = a[i] * inv % p;
        q[i - m] = coef;
        for (int j = 0; j <= m; j++) {
            a[i - m + j] = norm(a[i - m + j] - coef * b[j] % p, p);
        }
    }
    trim(q);
    trim(a);
    return {q, a};
}

Poly mod_poly(const Poly& a, const Poly& m, ll p) { return divmod_poly(a, m, p).second; }

Poly gcd_poly(Poly a, Poly b, ll p) {
    trim(a);
    trim(b);
    while (!b.empty()) {
        Poly r = mod_poly(a, b, p);
        a = b;
        b = r;
    }
    trim(a);
    if (a.empty()) return {};
    ll inv = mod_inv(a.back(), p);
    for (ll& x : a) x = x * inv % p;
    return a;
}

Poly mul_mod(const Poly& a, const Poly& b, const Poly& m, ll p) {
    return mod_poly(mul(a, b, p), m, p);
}

Poly pow_mod_poly(Poly a, ll e, const Poly& m, ll p) {
    Poly r = mod_poly({1}, m, p);
    a = mod_poly(a, m, p);
    while (e) {
        if (e & 1) r = mul_mod(r, a, m, p);
        e >>= 1;
        if (e) a = mul_mod(a, a, m, p);
    }
    return r;
}

vector<int> prime_divisors(int n) {
    vector<int> res;
    for (int p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            res.push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

vector<ll> prime_divisors_ll(ll n) {
    vector<ll> res;
    for (ll p = 2; p * p <= n; p++) {
        if (n % p == 0) {
            res.push_back(p);
            while (n % p == 0) n /= p;
        }
    }
    if (n > 1) res.push_back(n);
    return res;
}

bool is_prime_slow(ll n) {
    if (n <= 1) return false;
    for (ll d = 2; d * d <= n; d++) {
        if (n % d == 0) return false;
    }
    return true;
}

ll radical(int n) {
    ll r = 1;
    for (int q : prime_divisors(n)) r *= q;
    return r;
}

ll choose_prime(Random& gen);

// For x^n - a to be irreducible with a primitive root a, every prime
// divisor of n must divide p - 1. If 4 | n, we also need 4 | p - 1.
// This returns the modulus m such that choosing p = 1 mod m satisfies them.
ll binomial_prime_requirement(int n) {
    ll m = radical(n);
    if (n % 4 == 0) m = lcm(m, 4LL);
    return m;
}

ll choose_prime_for_binomials(Random& gen, const vector<int>& degrees) {
    ll m = 1;
    for (int d : degrees) {
        if (d <= 1) continue;
        m = lcm(m, binomial_prime_requirement(d));
    }
    if (m == 1) return choose_prime(gen);
    assert(m < P_MAX);
    ll k_max = (P_MAX - 1) / m;
    for (int t = 0; t < 20000; t++) {
        ll k = gen.uniform<ll>(1, k_max);
        ll p = k * m + 1;
        if (is_prime_slow(p)) return p;
    }
    for (ll k = 1; k <= k_max; k++) {
        ll p = k * m + 1;
        if (is_prime_slow(p)) return p;
    }
    assert(false);
}

ll primitive_root(ll p) {
    vector<ll> qs = prime_divisors_ll(p - 1);
    for (ll g = 2; g < p; g++) {
        bool ok = true;
        for (ll q : qs) {
            if (mod_pow(g, (p - 1) / q, p) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
    assert(false);
}

vector<int> binomial_degrees(int upper, ll p) {
    vector<int> res;
    for (int d = 1; d <= upper; d++) {
        ll m = binomial_prime_requirement(d);
        if ((p - 1) % m == 0) res.push_back(d);
    }
    assert(!res.empty());
    return res;
}

int choose_binomial_degree(Random& gen, int upper, ll p) {
    vector<int> ds = binomial_degrees(upper, p);
    return ds[gen.uniform<int>(0, (int)ds.size() - 1)];
}

int max_binomial_degree(int upper, ll p) {
    vector<int> ds = binomial_degrees(upper, p);
    return ds.back();
}

ll choose_prime_for_large_binomial_degree(Random& gen, int upper) {
    int best = 0;
    vector<ll> ps;
    for (ll p : PRIME_CANDIDATES) {
        int d = max_binomial_degree(upper, p);
        if (d > best) {
            best = d;
            ps.clear();
        }
        if (d == best) ps.push_back(p);
    }
    return ps[gen.uniform<int>(0, (int)ps.size() - 1)];
}

bool is_one(const Poly& a) { return a.size() == 1 && a[0] == 1; }
bool is_zero(const Poly& a) { return a.empty(); }

bool is_irreducible(const Poly& f, ll p) {
    int d = deg(f);
    if (d <= 0 || f.back() != 1) return false;
    const Poly x = {0, 1};
    const Poly x_mod = mod_poly(x, f, p);
    for (int r : prime_divisors(d)) {
        Poly h = x;
        for (int i = 0; i < d / r; i++) h = pow_mod_poly(h, p, f, p);
        if (!is_one(gcd_poly(f, sub(h, x_mod, p), p))) return false;
    }
    Poly h = x;
    for (int i = 0; i < d; i++) h = pow_mod_poly(h, p, f, p);
    return is_zero(sub(h, x_mod, p));
}

ll choose_prime(Random& gen) {
    return PRIME_CANDIDATES[gen.uniform<int>(0, (int)PRIME_CANDIDATES.size() - 1)];
}

Poly random_monic(Random& gen, int d, ll p) {
    Poly f(d + 1);
    for (int i = 0; i < d; i++) f[i] = gen.uniform<ll>(0, p - 1);
    f[d] = 1;
    return f;
}

Poly random_irreducible(Random& gen, int d, ll p) {
    while (true) {
        Poly f = random_monic(gen, d, p);
        if (is_irreducible(f, p)) return f;
    }
}

// Constructs (x + b)^d - a, where a is a primitive root modulo p.
// If every prime divisor of d divides p - 1, and additionally p = 1 mod 4
// when 4 divides d, then x^d - a is irreducible over F_p.  
// See lemma 6 of https://arxiv.org/pdf/1504.01172.
Poly shifted_binomial_irreducible(Random& gen, int d, ll p) {
    if (d == 1) return random_monic(gen, 1, p);
    ll a = primitive_root(p);
    ll b = gen.uniform<ll>(0, p - 1);
    Poly f = {1};
    Poly base = {b, 1};
    for (int i = 0; i < d; i++) f = mul(f, base, p);
    f[0] = norm(f[0] - a, p);
    trim(f);
    assert((int)f.size() == d + 1 && f.back() == 1);
    return f;
}

string key(const Poly& a) {
    string s;
    for (ll x : a) {
        s += to_string(x);
        s += ',';
    }
    return s;
}

void print_case(ll p, const Poly& f) {
    int n = (int)f.size() - 1;
    printf("%d %lld\n", n, p);
    for (int i = 0; i <= n; i++) {
        if (i) printf(" ");
        printf("%lld", f[i]);
    }
    printf("\n");
}
