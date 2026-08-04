#include <algorithm>
#include <cstdint>
#include <cstdio>
#include <queue>
#include <utility>
#include <vector>

using namespace std;

using ll = long long;
using Poly = vector<ll>;

ll mod;
uint64_t rng_state = 88172645463325252ULL;

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

Poly add(Poly a, const Poly& b) {
    if (a.size() < b.size()) a.resize(b.size());
    for (int i = 0; i < (int)b.size(); i++) {
        a[i] += b[i];
        if (a[i] >= mod) a[i] -= mod;
    }
    trim(a);
    return a;
}

Poly sub(Poly a, const Poly& b) {
    if (a.size() < b.size()) a.resize(b.size());
    for (int i = 0; i < (int)b.size(); i++) {
        a[i] -= b[i];
        if (a[i] < 0) a[i] += mod;
    }
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
        if (coef == 0) continue;
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

uint64_t next_rand() {
    rng_state ^= rng_state << 7;
    rng_state ^= rng_state >> 9;
    return rng_state;
}

Poly random_poly(int n) {
    Poly a(n);
    for (int i = 0; i < n; i++) a[i] = next_rand() % mod;
    trim(a);
    return a;
}

Poly equal_degree_power_odd(const Poly& a, int d, const Poly& m) {
    Poly x = pow_mod_poly(a, (mod - 1) / 2, m);
    Poly r = mod_poly({1}, m);
    for (int i = 0; i < d; i++) {
        r = mul_mod(r, x, m);
        if (i + 1 < d) x = pow_mod_poly(x, mod, m);
    }
    return r;
}

Poly equal_degree_trace_two(const Poly& a, int d, const Poly& m) {
    Poly y = mod_poly(a, m);
    Poly r;
    for (int i = 0; i < d; i++) {
        r = add(r, y);
        if (i + 1 < d) y = mul_mod(y, y, m);
    }
    return r;
}

vector<Poly> equal_degree_factor(Poly f, int d) {
    f = monic(f);
    vector<Poly> res;
    queue<Poly> q;
    q.push(f);
    while (!q.empty()) {
        Poly cur = monic(q.front());
        q.pop();
        int cd = deg(cur);
        if (cd == d) {
            res.push_back(cur);
            continue;
        }
        Poly g;
        do {
            Poly a = random_poly(cd);
            Poly h = (mod == 2) ? equal_degree_trace_two(a, d, cur)
                                : sub(equal_degree_power_odd(a, d, cur), {1});
            g = gcd_poly(cur, h);
        } while (deg(g) <= 0 || deg(g) == cd);
        q.push(g);
        q.push(divmod_poly(cur, g).first);
    }
    return res;
}

struct Factor {
    Poly f;
    int e;
};

vector<Factor> factorize(Poly f) {
    f = monic(f);
    vector<Factor> ans;
    if (deg(f) <= 0) return ans;
    const Poly x = {0, 1};
    Poly h = x;
    for (int d = 1; deg(f) > 0 && 2 * d <= deg(f); d++) {
        h = pow_mod_poly(h, mod, f);
        Poly g = gcd_poly(f, sub(h, x));
        if (deg(g) > 0) {
            for (Poly fac : equal_degree_factor(g, d)) {
                int e = 0;
                while (deg(f) >= deg(fac)) {
                    auto qr = divmod_poly(f, fac);
                    if (!qr.second.empty()) break;
                    f = qr.first;
                    e++;
                }
                ans.push_back({fac, e});
            }
        }
    }
    if (deg(f) > 0) ans.push_back({monic(f), 1});
    return ans;
}

int main() {
    int n;
    if (scanf("%d %lld", &n, &mod) != 2) return 1;
    Poly f(n + 1);
    for (int i = 0; i <= n; i++) scanf("%lld", &f[i]);
    vector<Factor> ans = factorize(f);
    printf("%d\n", (int)ans.size());
    for (auto& it : ans) {
        printf("%d %d", it.e, (int)it.f.size() - 1);
        for (ll x : it.f) printf(" %lld", x);
        printf("\n");
    }
    return 0;
}
