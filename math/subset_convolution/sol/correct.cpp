#include <iostream>
#include <vector>
#include <array>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

int popcnt(uint x) { return __builtin_popcount(x); }

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

using A = array<Mint, 21>;
int main() {
    int n;
    scanf("%d", &n);
    assert(n <= 20);
    V<A> a(1 << n), b(1 << n);
    for (uint i = 0; i < (1 << n); i++) {
        int x = 1;
        scanf("%d", &x);
        a[i][popcnt(i)] = x;
    }
    for (uint i = 0; i < (1 << n); i++) {
        int x = 1;
        scanf("%d", &x);
        b[i][popcnt(i)] = x;
    }

    for (int h = 0; h < n; h++) {
        for (int i = 0; i < (1 << n); i++) {
            if (i & (1 << h)) continue;
            for (int k = 0; k <= n; k++) {
                a[i | (1 << h)][k] += a[i][k];
            }
        }
    }
    for (int h = 0; h < n; h++) {
        for (int i = 0; i < (1 << n); i++) {
            if (i & (1 << h)) continue;
            for (int k = 0; k <= n; k++) {
                b[i | (1 << h)][k] += b[i][k];
            }
        }
    }

    for (int i = 0; i < (1 << n); i++) {
        A c = A();
        for (int k = 0; k <= n; k++) {
            for (int l = 0; l <= k; l++) {
                c[k] += a[i][l] * b[i][k - l];
            }
        }
        a[i] = c;
    }

    for (int h = 0; h < n; h++) {
        for (int i = 0; i < (1 << n); i++) {
            if (i & (1 << h)) continue;
            for (int k = 0; k <= n; k++) {
                a[i | (1 << h)][k] -= a[i][k];
            }
        }
    }

    for (uint k = 0; k < (1 << n); k++) {
        printf("%d", a[k][popcnt(k)].v);
        if (k != (1 << n) - 1) printf(" ");
    }
    printf("\n");
    return 0;
}
