#include <algorithm>
#include <set>
#include <string>
#include <utility>
#include <vector>
#include "testlib.h"

using namespace std;

using ll = long long;
using Poly = vector<ll>;

ll mod;

ll norm(ll x) {
    x %= mod;
    if (x < 0) x += mod;
    return x;
}

ll mod_pow(ll a, ll e) {
    ll r = 1 % mod;
    while (e) {
        if (e & 1) r = r * a % mod;
        a = a * a % mod;
        e >>= 1;
    }
    return r;
}

ll mod_inv(ll a) { return mod_pow(a, mod - 2); }

void trim(Poly& a) {
    while (!a.empty() && a.back() == 0) a.pop_back();
}

int deg(Poly a) {
    trim(a);
    return (int)a.size() - 1;
}

Poly monic(Poly a) {
    trim(a);
    if (a.empty()) return a;
    ll inv = mod_inv(a.back());
    for (ll& x : a) x = x * inv % mod;
    return a;
}

Poly sub(Poly a, const Poly& b) {
    if (a.size() < b.size()) a.resize(b.size());
    for (int i = 0; i < (int)b.size(); i++) a[i] = norm(a[i] - b[i]);
    trim(a);
    return a;
}

Poly mul(const Poly& a, const Poly& b) {
    if (a.empty() || b.empty()) return {};
    Poly c(a.size() + b.size() - 1);
    for (int i = 0; i < (int)a.size(); i++) {
        for (int j = 0; j < (int)b.size(); j++) {
            c[i + j] = (c[i + j] + a[i] * b[j]) % mod;
        }
    }
    trim(c);
    return c;
}

pair<Poly, Poly> divmod_poly(Poly a, Poly b) {
    trim(a);
    trim(b);
    int n = (int)a.size() - 1, m = (int)b.size() - 1;
    if (n < m) return {{}, a};
    Poly q(n - m + 1);
    ll inv = mod_inv(b.back());
    for (int i = n; i >= m; i--) {
        ll coef = a[i] * inv % mod;
        q[i - m] = coef;
        for (int j = 0; j <= m; j++) {
            a[i - m + j] = norm(a[i - m + j] - coef * b[j] % mod);
        }
    }
    trim(q);
    trim(a);
    return {q, a};
}

Poly mod_poly(const Poly& a, const Poly& m) { return divmod_poly(a, m).second; }

Poly gcd_poly(Poly a, Poly b) {
    trim(a);
    trim(b);
    while (!b.empty()) {
        Poly r = mod_poly(a, b);
        a = b;
        b = r;
    }
    return monic(a);
}

Poly mul_mod(const Poly& a, const Poly& b, const Poly& m) {
    return mod_poly(mul(a, b), m);
}

Poly pow_mod_poly(Poly a, ll e, const Poly& m) {
    Poly r = mod_poly({1}, m);
    a = mod_poly(a, m);
    while (e) {
        if (e & 1) r = mul_mod(r, a, m);
        e >>= 1;
        if (e) a = mul_mod(a, a, m);
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

bool is_one(const Poly& a) {
    return a.size() == 1 && a[0] == 1;
}

bool is_zero(const Poly& a) {
    return a.empty();
}

bool is_irreducible(const Poly& f) {
    int d = deg(f);
    if (d <= 0 || f.back() != 1) return false;
    const Poly x = {0, 1};
    const Poly x_mod = mod_poly(x, f);
    for (int r : prime_divisors(d)) {
        Poly h = x;
        for (int i = 0; i < d / r; i++) h = pow_mod_poly(h, mod, f);
        if (!is_one(gcd_poly(f, sub(h, x_mod)))) return false;
    }
    Poly h = x;
    for (int i = 0; i < d; i++) h = pow_mod_poly(h, mod, f);
    return is_zero(sub(h, x_mod));
}

Poly pow_poly(Poly a, int e) {
    Poly r = {1};
    while (e) {
        if (e & 1) r = mul(r, a);
        e >>= 1;
        if (e) a = mul(a, a);
    }
    return r;
}

string key(const Poly& a) {
    string s;
    for (ll x : a) {
        s += to_string(x);
        s += ',';
    }
    return s;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    mod = inf.readLong();
    Poly expected(n + 1);
    for (int i = 0; i <= n; i++) expected[i] = inf.readLong();
    trim(expected);

    int k = ouf.readInt(0, max(0, n), "K");
    set<string> seen;
    Poly actual = {1};
    int degree_sum = 0;
    for (int i = 0; i < k; i++) {
        int e = ouf.readInt(1, max(1, n), "e_i");
        int d = ouf.readInt(1, max(1, n), "d_i");
        Poly g(d + 1);
        for (int j = 0; j <= d; j++) g[j] = ouf.readLong(0LL, mod - 1, "b_i_j");
        if (g.back() != 1) quitf(_wa, "factor is not monic");
        if (!seen.insert(key(g)).second) quitf(_wa, "duplicated factor");
        if (!is_irreducible(g)) quitf(_wa, "factor is not irreducible");
        degree_sum += e * d;
        if (degree_sum > n) quitf(_wa, "total degree is too large");
        actual = mul(actual, pow_poly(g, e));
    }
    trim(actual);
    if (actual != expected) quitf(_wa, "product of factors differs from input polynomial");
    quitf(_ok, "OK");
}
