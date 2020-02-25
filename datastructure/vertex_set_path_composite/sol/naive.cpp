#include <iostream>
#include <vector>
#include <cassert>
#include <algorithm>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(uint(_v % MD + MD)); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(uint(ull(v) * r.v % MD)); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
using Mint = ModInt<998244353>;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    assert(ll(n) * q <= TEN(7));
    struct F {
        Mint a, b;
    };
    V<F> f(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        f[i] = {Mint(a), Mint(b)};
    }
    struct E { int to; };
    VV<int> tr(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        tr[u].push_back(v);
        tr[v].push_back(u);
    }
    for (int ph = 0; ph < q; ph++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int p;
            int c, d;
            scanf("%d %d %d", &p, &c, &d);
            f[p] = {Mint(c), Mint(d)};
        } else {
            int u, v;
            int _x;
            scanf("%d %d %d", &u, &v, &_x);
            Mint x = _x;

            V<int> path;
            auto dfs = [&](auto self, int p, int b) -> bool {
                if (p == v) {
                    path.push_back(p);
                    return true;
                }
                for (auto d: tr[p]) {
                    if (d == b) continue;
                    if (self(self, d, p)) {
                        path.push_back(p);
                        return true;
                    }
                }
                return false;
            };
            bool res = dfs(dfs, u, -1);
            assert(res);
            reverse(path.begin(), path.end());

            for (auto i: path) {
                x = f[i].a * x + f[i].b;
            }
            printf("%d\n", x.v);
        }
    }
    return 0;
}
