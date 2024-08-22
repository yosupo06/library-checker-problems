#include <cassert>
#include <cstdio>
#include <vector>

template <int m, std::enable_if_t<(1 <= m)>* = nullptr> struct static_modint {
    using mint = static_modint;

  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    static_modint() : _v(0) {}
    static_modint(long long v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }

    unsigned int val() const { return _v; }

    mint& operator++() {
        _v++;
        if (_v == umod()) _v = 0;
        return *this;
    }
    mint& operator--() {
        if (_v == 0) _v = umod();
        _v--;
        return *this;
    }
    mint operator++(int) {
        mint result = *this;
        ++*this;
        return result;
    }
    mint operator--(int) {
        mint result = *this;
        --*this;
        return result;
    }

    mint& operator+=(const mint& rhs) {
        _v += rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator-=(const mint& rhs) {
        _v -= rhs._v;
        if (_v >= umod()) _v += umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        unsigned long long z = _v;
        z *= rhs._v;
        _v = (unsigned int)(z % umod());
        return *this;
    }
    mint& operator/=(const mint& rhs) { return *this = *this * rhs.inv(); }

    mint operator+() const { return *this; }
    mint operator-() const { return mint() - *this; }

    mint pow(long long n) const {
        assert(0 <= n);
        mint x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    mint inv() const {
        assert(_v);
        return pow(umod() - 2);
    }

    friend mint operator+(const mint& lhs, const mint& rhs) {
        return mint(lhs) += rhs;
    }
    friend mint operator-(const mint& lhs, const mint& rhs) {
        return mint(lhs) -= rhs;
    }
    friend mint operator*(const mint& lhs, const mint& rhs) {
        return mint(lhs) *= rhs;
    }
    friend mint operator/(const mint& lhs, const mint& rhs) {
        return mint(lhs) /= rhs;
    }
    friend bool operator==(const mint& lhs, const mint& rhs) {
        return lhs._v == rhs._v;
    }
    friend bool operator!=(const mint& lhs, const mint& rhs) {
        return lhs._v != rhs._v;
    }

  private:
    unsigned int _v;
    static constexpr unsigned int umod() { return m; }
};
using mint = static_modint<998244353>;
using namespace std;

int main() {
    int k;
    scanf("%d", &k);
    vector<int> n(k);
    int N = 1;
    for (int i = 0; i < k; i++) {
        scanf("%d", &(n[i]));
        N *= n[i];
    }
    vector<mint> f(N), g(N);
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        f[i] = x;
    }
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        g[i] = x;
    }
    vector<mint> fg(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            bool ok = true;
            int ij = 0;
            int x = i, y = j;
            int base = 1;
            for (int l = 0; l < k; l++) {
                int xl = x % n[l];
                int yl = y % n[l];

                if (xl + yl >= n[l]) {
                    ok = false;
                    break;
                }
                ij += base * (xl + yl);

                x /= n[l];
                y /= n[l];
                base *= n[l];
            }
            if (!ok) continue;
            fg[ij] += f[i] * g[j];
        }
    }

    for (int i = 0; i < N; i++) {
        printf("%d", fg[i].val());
        if (i + 1 < N) printf(" ");
    }
    printf("\n");
    return 0;
}
