#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <complex>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <utility>

using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
using namespace std;
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

// bit op
int popcnt(uint x) { return __builtin_popcount(x); }
int popcnt(ull x) { return __builtin_popcountll(x); }
int bsr(uint x) { return 31 - __builtin_clz(x); }
int bsr(ull x) { return 63 - __builtin_clzll(x); }
int bsf(uint x) { return __builtin_ctz(x); }
int bsf(ull x) { return __builtin_ctzll(x); }

template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(uint(_v % MD + MD)); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    static constexpr uint get_mod() { return MD; }
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
// using Mint = ModInt<998244353>;
// template<> const Mint Mint::G = Mint(3);

template <class Mint> void nft(bool type, V<Mint>& a) {
    int n = int(a.size()), s = 0;
    while ((1 << s) < n) s++;
    assert(1 << s == n);

    static V<Mint> ep, iep;
    while (int(ep.size()) <= s) {
        ep.push_back(Mint::G.pow(Mint(-1).v / (1 << ep.size())));
        iep.push_back(ep.back().inv());
    }
    V<Mint> b(n);
    for (int i = 1; i <= s; i++) {
        int w = 1 << (s - i);
        Mint base = type ? iep[i] : ep[i], now = 1;
        for (int y = 0; y < n / 2; y += w) {
            for (int x = 0; x < w; x++) {
                auto l = a[y << 1 | x];
                auto r = now * a[y << 1 | x | w];
                b[y | x] = l + r;
                b[y | x | n >> 1] = l - r;
            }
            now *= base;
        }
        swap(a, b);
    }
}

template <class Mint> V<Mint> multiply_nft(const V<Mint>& a, const V<Mint>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (min(n, m) <= 8) {
        V<Mint> ans(n + m - 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];
        return ans;
    }
    int lg = 0;
    while ((1 << lg) < n + m - 1) lg++;
    int z = 1 << lg;
    auto a2 = a, b2 = b;
    a2.resize(z);
    b2.resize(z);
    nft(false, a2);
    nft(false, b2);
    for (int i = 0; i < z; i++) a2[i] *= b2[i];
    nft(true, a2);
    a2.resize(n + m - 1);
    Mint iz = Mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
    return a2;
}

// Cooley-Tukey: input -> butterfly -> bit reversing -> output から
// bit reversingを抜いたもの 直接使うな
template <class Mint> void butterfly(bool type, V<Mint>& a) {
    int n = int(a.size()), h = 0;
    while ((1 << h) < n) h++;
    assert(1 << h == n);
    if (n == 1) return;

    static V<Mint> snow, sinow;
    if (snow.empty()) {
        Mint sep = Mint(1), siep = Mint(1);
        uint mod = Mint(-1).v;
        uint di = 4;
        while (mod % di == 0) {
            Mint ep = Mint::G.pow(mod / di);
            Mint iep = ep.inv();
            snow.push_back(siep * ep);
            sinow.push_back(sep * iep);
            sep *= ep;
            siep *= iep;
            di *= 2;
        }
    }

    if (!type) {
        // fft
        for (int ph = 1; ph <= h; ph++) {
            // phase ph: size w -> 2w の FFT, p 並列
            int w = 1 << (ph - 1), p = 1 << (h - ph);
            Mint now = Mint(1);
            for (int s = 0; s < w; s++) {
                int offset = s << (h - ph + 1);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset];
                    auto r = a[i + offset + p] * now;
                    a[i + offset] = l + r;
                    a[i + offset + p] = l - r;
                }
                int u = bsf(~uint(s));
                now *= snow[u];
            }
        }
    } else {
        // ifft
        for (int ph = h; ph >= 1; ph--) {
            int w = 1 << (ph - 1), p = 1 << (h - ph);
            Mint inow = Mint(1);
            for (int s = 0; s < w; s++) {
                int offset = s << (h - ph + 1);
                for (int i = 0; i < p; i++) {
                    auto l = a[i + offset];
                    auto r = a[i + offset + p];
                    a[i + offset] = l + r;
                    a[i + offset + p] = (l - r) * inow;
                }
                int u = bsf(~uint(s));
                inow *= sinow[u];
            }
        }
    }
}

template <class Mint> V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (min(n, m) < 8) {
        V<Mint> ans(n + m - 1);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++) ans[i + j] += a[i] * b[j];
        return ans;
    }
    int lg = 0;
    while ((1 << lg) < n + m - 1) lg++;
    int z = 1 << lg;
    auto a2 = a;
    a2.resize(z);
    butterfly(false, a2);
    if (a == b) {
        for (int i = 0; i < z; i++) a2[i] *= a2[i];
    } else {
        auto b2 = b;
        b2.resize(z);
        butterfly(false, b2);
        for (int i = 0; i < z; i++) a2[i] *= b2[i];
    }
    butterfly(true, a2);
    a2.resize(n + m - 1);
    Mint iz = Mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a2[i] *= iz;
    return a2;
}

struct Centroid {
    int r;
    VV<int> tr;
    V<int> par;
};

template <class E> struct CentroidExec : Centroid {
    int n;
    const VV<E>& g;
    V<bool> used;

    using P = pair<int, int>;
    V<P> info;  //(child max, child)

    int dfs(int p, int b) {
        int sz = 1;
        info[p] = P(0, -1);
        for (E e : g[p]) {
            int d = e.to;
            if (d == b || used[d]) continue;
            int csz = dfs(d, p);
            sz += csz;
            info[p] = max(info[p], P(csz, d));
        }
        return sz;
    }
    int init(int p, int b) {
        int sz = dfs(p, -1);
        while (info[p].first > sz / 2) p = info[p].second;
        par[p] = b;
        used[p] = true;
        for (E e : g[p]) {
            int d = e.to;
            if (used[d]) continue;
            tr[p].push_back(init(d, p));
        }
        return p;
    }
    CentroidExec(const VV<E>& _g) : n(int(_g.size())), g(_g), used(n), info(n) {
        tr = VV<int>(n);
        par = V<int>(n);
        r = init(0, -1);
    }
};

template <class E> Centroid get_centroid(const VV<E>& g) {
    return CentroidExec<E>(g);
}

using Mint0 = ModInt<998244353>;
template <> const Mint0 Mint0::G = Mint0(3);

using Mint1 = ModInt<924844033>;
template <> const Mint1 Mint1::G = Mint1(5);

struct E {
    int to;
};

template <class Mint> V<Mint> solve(VV<E> g) {
    int n = int(g.size());

    Centroid cent = get_centroid(g);
    V<bool> vis(n);
    V<Mint> buf;

    auto dfs = [&](auto self, int p, int b, int ndp) -> void {
        if (vis[p]) return;

        while (int(buf.size()) <= ndp) buf.push_back(Mint(0));
        buf[ndp] += Mint(1);

        for (auto e : g[p]) {
            int d = e.to;
            if (d == b) continue;
            self(self, d, p, ndp + 1);
        }
    };

    V<Mint> cnt(n);

    auto cent_dfs = [&](auto self, int r) -> void {
        V<Mint> sm = {Mint(1)};
        for (auto e : g[r]) {
            int d = e.to;
            buf.clear();
            dfs(dfs, d, r, 1);
            int m = int(buf.size());
            while (int(sm.size()) < m) sm.push_back(Mint(0));
            for (int i = 0; i < m; i++) sm[i] += buf[i];
            buf = multiply(buf, buf);
            m = int(buf.size());
            for (int i = 0; i < m; i++) cnt[i] -= buf[i];
        }

        sm = multiply(sm, sm);
        int m = int(sm.size());
        for (int i = 0; i < m; i++) cnt[i] += sm[i];

        vis[r] = true;
        for (auto d : cent.tr[r]) {
            self(self, d);
        }
    };

    cent_dfs(cent_dfs, cent.r);

    return cnt;
}

using Int = __int128_t;

/// g:gcd(a, b), ax+by=g
struct EG { Int g, x, y; };
EG ext_gcd(Int a, Int b) {
    if (b == 0) {
        if (a >= 0) return EG{a, 1, 0};
        else return EG{-a, -1, 0};
    } else {
        auto e = ext_gcd(b, a % b);
        return EG{e.g, e.y, e.x - a / b * e.y};
    }
}

// (rem, mod)
pair<Int, Int> crt(const V<Int>& b, const V<Int>& c) {
    int n = int(b.size());
    Int r = 0, m = 1;
    for (int i = 0; i < n; i++) {
        auto eg = ext_gcd(m, c[i]);
        Int g = eg.g, im = eg.x;
        if ((b[i] - r) % g) return {0, -1};
        Int tmp = (b[i] - r) / g * im % (c[i] / g);
        r += m * tmp;
        m *= c[i] / g;
    }
    return {(r % m + m) % m, m};
}

int main() {
    int n;
    scanf("%d", &n);
 
    auto g = VV<E>(n);
 
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back({b});
        g[b].push_back({a});
    }

    V<Mint0> ans0 = solve<Mint0>(g);
    V<Mint1> ans1 = solve<Mint1>(g);

    for (int i = 1; i <= n - 1; i++) {
        Int x = ans0[i].v;
        Int y = ans1[i].v;
        Int z = crt({x, y}, {Mint0::get_mod(), Mint1::get_mod()}).first;
        if (i != 1) printf(" ");
        printf("%lld", ll(z / 2));
    }
    printf("\n");
    return 0;
}
