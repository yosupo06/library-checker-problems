#include <cassert>
#include <cstdio>
#include <vector>
#include <array>

template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint {
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

int bsf(unsigned int n) {
    return __builtin_ctz(n);
}

int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

void butterfly(std::vector<mint>& a) {
    static constexpr int g = 3;
    int n = int(a.size());
    int h = ceil_pow2(n);

    static bool first = true;
    static mint sum_e[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]
    if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_e[i] = es[i] * now;
            now *= ies[i];
        }
    }
    for (int ph = 1; ph <= h; ph++) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint now = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = a[i + offset];
                auto r = a[i + offset + p] * now;
                a[i + offset] = l + r;
                a[i + offset + p] = l - r;
            }
            now *= sum_e[bsf(~(unsigned int)(s))];
        }
    }
}

void butterfly_inv(std::vector<mint>& a) {
    static constexpr int g = 3;
    int n = int(a.size());
    int h = ceil_pow2(n);

    static bool first = true;
    static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
            // e^(2^i) == 1
            es[i - 2] = e;
            ies[i - 2] = ie;
            e *= e;
            ie *= ie;
        }
        mint now = 1;
        for (int i = 0; i <= cnt2 - 2; i++) {
            sum_ie[i] = ies[i] * now;
            now *= es[i];
        }
    }

    for (int ph = h; ph >= 1; ph--) {
        int w = 1 << (ph - 1), p = 1 << (h - ph);
        mint inow = 1;
        for (int s = 0; s < w; s++) {
            int offset = s << (h - ph + 1);
            for (int i = 0; i < p; i++) {
                auto l = a[i + offset];
                auto r = a[i + offset + p];
                a[i + offset] = l + r;
                a[i + offset + p] =
                    (unsigned long long)(mint::mod() + l.val() - r.val()) *
                    inow.val();
            }
            inow *= sum_ie[bsf(~(unsigned int)(s))];
        }
    }
}

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

    if (k == 0) {
        int x, y;
        scanf("%d%d", &x, &y);
        int z = (mint(x) * mint(y)).val();
        printf("%d\n", z);
        return 0;
    }
    auto chi = [&](int x) {
        int sum = 0;
        int base = 1;
        for (int i = 0; i < k - 1; i++) {
            base *= n[i];
            sum += x / base;
        }
        return sum;
    };
    int S = 1;
    while (S < 2 * N) S *= 2;
    vector<vector<mint>> f(k, vector<mint>(S)), g(k, vector<mint>(S));
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        f[chi(i) % k][i] = x;
    }
    for (int i = 0; i < N; i++) {
        int x;
        scanf("%d", &x);
        g[chi(i) % k][i] = x;
    }
    for (int j = 0; j < k; j++) {
        butterfly(f[j]);
        butterfly(g[j]);
    }

    vector<vector<mint>> fg(k, vector<mint>(S));
    for (int l = 0; l < k; l++) {
        for (int r = 0; r < k; r++) {
            int lr = (l + r >= k) ? (l + r - k) : l + r;
            for (int i = 0; i < S; i++) {
                fg[lr][i] += f[l][i] * g[r][i];
            }
        }
    }

    for (int j = 0; j < k; j++) {
        butterfly_inv(fg[j]);
    }

    const mint iS = mint(S).inv();
    for (int i = 0; i < N; i++) {
        printf("%d", (fg[chi(i) % k][i] * iS).val());
        if (i + 1 < N) printf(" ");
    }
    printf("\n");
    return 0;
}
