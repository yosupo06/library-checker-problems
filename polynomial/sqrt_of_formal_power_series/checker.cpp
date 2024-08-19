#include <algorithm>
#include <iostream>
#include <cassert>
#include "testlib.h"

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
template <class T> using V = vector<T>;

template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(_v % MD + MD); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(ull(v) * r.v % MD); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    bool operator!=(const M& r) const { return v != r.v; }
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
template <> const Mint Mint::G = Mint(3);

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

template <class Mint> V<Mint> multiply(const V<Mint>& a, const V<Mint>& b) {
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


bool has_sqrt(Mint y) {
    return (y.v == 0 || y.pow(Mint(-1).v / 2).v == 1);
}

bool has_sqrt(vector<Mint> pol) {
    while (pol.size() && !pol.back()) pol.pop_back();
    if (pol.empty()) return true;
    size_t low_deg = 0;
    while (!pol[low_deg]) low_deg++;
    if (low_deg % 2) return false;
    return has_sqrt(pol[low_deg]);
}

bool read_ans(InStream& stream, vector<Mint> expect) {
    int n = int(expect.size());
    int first = stream.readInt();
    if (first == -1) return false;    
    vector<Mint> pol(n);
    pol[0] = first;
    for (int i = 1; i < n; i++) {
        pol[i] = stream.readInt();
    }


    auto pol2 = multiply(pol, pol);

    for (int i = 0; i < n; i++) {
        if (pol2[i] != expect[i]) {
            quitf(_wa, "Invalid output: f(x) != g(x) * g(x)");
        }
    }

    return true;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    vector<Mint> pol(n);
    for (int i = 0; i < n; i++) {
        pol[i] = inf.readInt();
    }

    bool expect = has_sqrt(pol);
    bool actual = read_ans(ouf, pol);


    if (expect && !actual) {
        quitf(_wa, "you cannot find g(x)");
    }
    if (!expect && actual) {
        quitf(_fail, "what happened???");
    }
    quitf(_ok, "OK");
}
