// g++-13 library-count_increasing_sequences.cpp -std=c++17 -O2 -I .

// https://noshi91.hatenablog.com/entry/2023/07/21/235339


#include <cassert>
#include <numeric>
#include <type_traits>

#ifdef _MSC_VER
#include <intrin.h>
#endif


#include <utility>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#include <iostream>
using namespace std;

namespace atcoder {

namespace internal {

constexpr long long safe_mod(long long x, long long m) {
    x %= m;
    if (x < 0) x += m;
    return x;
}

struct barrett {
    unsigned int _m;
    unsigned long long im;

    explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

    unsigned int umod() const { return _m; }
    
    unsigned int mul(unsigned int a, unsigned int b) const {

        unsigned long long z = a;
        z *= b;
#ifdef _MSC_VER
        unsigned long long x;
        _umul128(z, im, &x);
#else
        unsigned long long x =
            (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
        unsigned int v = (unsigned int)(z - x * _m);
        if (_m <= v) v += _m;
        return v;
    }
};

constexpr long long pow_mod_constexpr(long long x, long long n, int m) {
    if (m == 1) return 0;
    unsigned int _m = (unsigned int)(m);
    unsigned long long r = 1;
    unsigned long long y = safe_mod(x, m);
    while (n) {
        if (n & 1) r = (r * y) % _m;
        y = (y * y) % _m;
        n >>= 1;
    }
    return r;
}

constexpr bool is_prime_constexpr(int n) {
    if (n <= 1) return false;
    if (n == 2 || n == 7 || n == 61) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    constexpr long long bases[3] = {2, 7, 61};
    for (long long a : bases) {
        long long t = d;
        long long y = pow_mod_constexpr(a, t, n);
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = y * y % n;
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}
template <int n> constexpr bool is_prime = is_prime_constexpr(n);

constexpr std::pair<long long, long long> inv_gcd(long long a, long long b) {
    a = safe_mod(a, b);
    if (a == 0) return {b, 0};

    long long s = b, t = a;
    long long m0 = 0, m1 = 1;

    while (t) {
        long long u = s / t;
        s -= t * u;
        m0 -= m1 * u;  // |m1 * u| <= |m1| * s <= b


        auto tmp = s;
        s = t;
        t = tmp;
        tmp = m0;
        m0 = m1;
        m1 = tmp;
    }
    if (m0 < 0) m0 += b / s;
    return {s, m0};
}

constexpr int primitive_root_constexpr(int m) {
    if (m == 2) return 1;
    if (m == 167772161) return 3;
    if (m == 469762049) return 3;
    if (m == 754974721) return 11;
    if (m == 998244353) return 3;
    int divs[20] = {};
    divs[0] = 2;
    int cnt = 1;
    int x = (m - 1) / 2;
    while (x % 2 == 0) x /= 2;
    for (int i = 3; (long long)(i)*i <= x; i += 2) {
        if (x % i == 0) {
            divs[cnt++] = i;
            while (x % i == 0) {
                x /= i;
            }
        }
    }
    if (x > 1) {
        divs[cnt++] = x;
    }
    for (int g = 2;; g++) {
        bool ok = true;
        for (int i = 0; i < cnt; i++) {
            if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1) {
                ok = false;
                break;
            }
        }
        if (ok) return g;
    }
}
template <int m> constexpr int primitive_root = primitive_root_constexpr(m);

unsigned long long floor_sum_unsigned(unsigned long long n,
                                      unsigned long long m,
                                      unsigned long long a,
                                      unsigned long long b) {
    unsigned long long ans = 0;
    while (true) {
        if (a >= m) {
            ans += n * (n - 1) / 2 * (a / m);
            a %= m;
        }
        if (b >= m) {
            ans += n * (b / m);
            b %= m;
        }

        unsigned long long y_max = a * n + b;
        if (y_max < m) break;
        n = (unsigned long long)(y_max / m);
        b = (unsigned long long)(y_max % m);
        std::swap(m, a);
    }
    return ans;
}

}  // namespace internal

}  // namespace atcoder


#include <cassert>
#include <numeric>
#include <type_traits>

namespace atcoder {

namespace internal {

#ifndef _MSC_VER
template <class T>
using is_signed_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value ||
                                  std::is_same<T, __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int128 =
    typename std::conditional<std::is_same<T, __uint128_t>::value ||
                                  std::is_same<T, unsigned __int128>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using make_unsigned_int128 =
    typename std::conditional<std::is_same<T, __int128_t>::value,
                              __uint128_t,
                              unsigned __int128>;

template <class T>
using is_integral = typename std::conditional<std::is_integral<T>::value ||
                                                  is_signed_int128<T>::value ||
                                                  is_unsigned_int128<T>::value,
                                              std::true_type,
                                              std::false_type>::type;

template <class T>
using is_signed_int = typename std::conditional<(is_integral<T>::value &&
                                                 std::is_signed<T>::value) ||
                                                    is_signed_int128<T>::value,
                                                std::true_type,
                                                std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<(is_integral<T>::value &&
                               std::is_unsigned<T>::value) ||
                                  is_unsigned_int128<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<
    is_signed_int128<T>::value,
    make_unsigned_int128<T>,
    typename std::conditional<std::is_signed<T>::value,
                              std::make_unsigned<T>,
                              std::common_type<T>>::type>::type;

#else

template <class T> using is_integral = typename std::is_integral<T>;

template <class T>
using is_signed_int =
    typename std::conditional<is_integral<T>::value && std::is_signed<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using is_unsigned_int =
    typename std::conditional<is_integral<T>::value &&
                                  std::is_unsigned<T>::value,
                              std::true_type,
                              std::false_type>::type;

template <class T>
using to_unsigned = typename std::conditional<is_signed_int<T>::value,
                                              std::make_unsigned<T>,
                                              std::common_type<T>>::type;

#endif

template <class T>
using is_signed_int_t = std::enable_if_t<is_signed_int<T>::value>;

template <class T>
using is_unsigned_int_t = std::enable_if_t<is_unsigned_int<T>::value>;

template <class T> using to_unsigned_t = typename to_unsigned<T>::type;

}  // namespace internal

}  // namespace atcoder


namespace atcoder {

namespace internal {

struct modint_base {};
struct static_modint_base : modint_base {};

template <class T> using is_modint = std::is_base_of<modint_base, T>;
template <class T> using is_modint_t = std::enable_if_t<is_modint<T>::value>;

}  // namespace internal

template <int m, std::enable_if_t<(1 <= m)>* = nullptr>
struct static_modint : internal::static_modint_base {
    using mint = static_modint;

  public:
    static constexpr int mod() { return m; }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    static_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    static_modint(T v) {
        long long x = (long long)(v % (long long)(umod()));
        if (x < 0) x += umod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    static_modint(T v) {
        _v = (unsigned int)(v % umod());
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
        if (prime) {
            assert(_v);
            return pow(umod() - 2);
        } else {
            auto eg = internal::inv_gcd(_v, m);
            assert(eg.first == 1);
            return eg.second;
        }
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
    static constexpr bool prime = internal::is_prime<m>;
};

template <int id> struct dynamic_modint : internal::modint_base {
    using mint = dynamic_modint;

  public:
    static int mod() { return (int)(bt.umod()); }
    static void set_mod(int m) {
        assert(1 <= m);
        bt = internal::barrett(m);
    }
    static mint raw(int v) {
        mint x;
        x._v = v;
        return x;
    }

    dynamic_modint() : _v(0) {}
    template <class T, internal::is_signed_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        long long x = (long long)(v % (long long)(mod()));
        if (x < 0) x += mod();
        _v = (unsigned int)(x);
    }
    template <class T, internal::is_unsigned_int_t<T>* = nullptr>
    dynamic_modint(T v) {
        _v = (unsigned int)(v % mod());
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
        _v += mod() - rhs._v;
        if (_v >= umod()) _v -= umod();
        return *this;
    }
    mint& operator*=(const mint& rhs) {
        _v = bt.mul(_v, rhs._v);
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
        auto eg = internal::inv_gcd(_v, mod());
        assert(eg.first == 1);
        return eg.second;
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
    static internal::barrett bt;
    static unsigned int umod() { return bt.umod(); }
};
template <int id> internal::barrett dynamic_modint<id>::bt(998244353);

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
using modint = dynamic_modint<-1>;

namespace internal {

template <class T>
using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

template <class T>
using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

template <class> struct is_dynamic_modint : public std::false_type {};
template <int id>
struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type {};

template <class T>
using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

}  // namespace internal

}  // namespace atcoder


#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <vector>


#ifdef _MSC_VER
#include <intrin.h>
#endif

namespace atcoder {

namespace internal {

int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

int bsf(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

}  // namespace internal

}  // namespace atcoder


namespace atcoder {

namespace internal {

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
void butterfly(std::vector<mint>& a) {
    static constexpr int g = internal::primitive_root<mint::mod()>;
    int n = int(a.size());
    int h = internal::ceil_pow2(n);

    static bool first = true;
    static mint sum_e[30];  // sum_e[i] = ies[0] * ... * ies[i - 1] * es[i]
    if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
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

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
void butterfly_inv(std::vector<mint>& a) {
    static constexpr int g = internal::primitive_root<mint::mod()>;
    int n = int(a.size());
    int h = internal::ceil_pow2(n);

    static bool first = true;
    static mint sum_ie[30];  // sum_ie[i] = es[0] * ... * es[i - 1] * ies[i]
    if (first) {
        first = false;
        mint es[30], ies[30];  // es[i]^(2^(2+i)) == 1
        int cnt2 = bsf(mint::mod() - 1);
        mint e = mint(g).pow((mint::mod() - 1) >> cnt2), ie = e.inv();
        for (int i = cnt2; i >= 2; i--) {
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

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution_naive(const std::vector<mint>& a, const std::vector<mint>& b) {
    int n = int(a.size()), m = int(b.size());
    std::vector<mint> ans(n + m - 1);
    if (n < m) {
        for (int j = 0; j < m; j++) {
            for (int i = 0; i < n; i++) {
                ans[i + j] += a[i] * b[j];
            }
        }
    } else {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                ans[i + j] += a[i] * b[j];
            }
        }
    }
    return ans;
}

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b) {
    int n = int(a.size()), m = int(b.size());
    int z = 1 << internal::ceil_pow2(n + m - 1);
    a.resize(z);
    internal::butterfly(a);
    b.resize(z);
    internal::butterfly(b);
    for (int i = 0; i < z; i++) {
        a[i] *= b[i];
    }
    internal::butterfly_inv(a);
    a.resize(n + m - 1);
    mint iz = mint(z).inv();
    for (int i = 0; i < n + m - 1; i++) a[i] *= iz;
    return a;
}

}  // namespace internal

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution(std::vector<mint>&& a, std::vector<mint>&& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (std::min(n, m) <= 60) return convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}

template <class mint, internal::is_static_modint_t<mint>* = nullptr>
std::vector<mint> convolution(const std::vector<mint>& a, const std::vector<mint>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};
    if (std::min(n, m) <= 60) return convolution_naive(a, b);
    return internal::convolution_fft(a, b);
}

template <unsigned int mod = 998244353,
          class T,
          std::enable_if_t<internal::is_integral<T>::value>* = nullptr>
std::vector<T> convolution(const std::vector<T>& a, const std::vector<T>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    using mint = static_modint<mod>;
    std::vector<mint> a2(n), b2(m);
    for (int i = 0; i < n; i++) {
        a2[i] = mint(a[i]);
    }
    for (int i = 0; i < m; i++) {
        b2[i] = mint(b[i]);
    }
    auto c2 = convolution(move(a2), move(b2));
    std::vector<T> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        c[i] = c2[i].val();
    }
    return c;
}

std::vector<long long> convolution_ll(const std::vector<long long>& a,
                                      const std::vector<long long>& b) {
    int n = int(a.size()), m = int(b.size());
    if (!n || !m) return {};

    static constexpr unsigned long long MOD1 = 754974721;  // 2^24
    static constexpr unsigned long long MOD2 = 167772161;  // 2^25
    static constexpr unsigned long long MOD3 = 469762049;  // 2^26
    static constexpr unsigned long long M2M3 = MOD2 * MOD3;
    static constexpr unsigned long long M1M3 = MOD1 * MOD3;
    static constexpr unsigned long long M1M2 = MOD1 * MOD2;
    static constexpr unsigned long long M1M2M3 = MOD1 * MOD2 * MOD3;

    static constexpr unsigned long long i1 =
        internal::inv_gcd(MOD2 * MOD3, MOD1).second;
    static constexpr unsigned long long i2 =
        internal::inv_gcd(MOD1 * MOD3, MOD2).second;
    static constexpr unsigned long long i3 =
        internal::inv_gcd(MOD1 * MOD2, MOD3).second;

    auto c1 = convolution<MOD1>(a, b);
    auto c2 = convolution<MOD2>(a, b);
    auto c3 = convolution<MOD3>(a, b);

    std::vector<long long> c(n + m - 1);
    for (int i = 0; i < n + m - 1; i++) {
        unsigned long long x = 0;
        x += (c1[i] * i1) % MOD1 * M2M3;
        x += (c2[i] * i2) % MOD2 * M1M3;
        x += (c3[i] * i3) % MOD3 * M1M2;
        long long diff =
            c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
        if (diff < 0) diff += MOD1;
        static constexpr unsigned long long offset[5] = {
            0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
        x -= offset[diff % 5];
        c[i] = x;
    }

    return c;
}

}  // namespace atcoder


using namespace std;
using namespace atcoder;


#include <iostream>

// 以下を満たす "広義" 単調増加の整数列 x を数える
// a_i <= x_i <= b_i
// a,b の単調性は要求しない(内部で補正する)
// ただし、 a,b が非負整数列であることは要求される
struct number_of_increasing_sequences_between_two_sequences{
private:
  using ll = long long;
  using mint = static_modint<998244353>;

  #define all(a) a.begin(),a.end()
  #define rep(i,start,end) for(ll i=start;i<(ll)(end);i++)
  #define per(i,start,end) for(ll i=start;i>=(ll)(end);i--)

  int n;
  vector<int> a,b;
  int zelo_flg=0;
  long long mod = 998244353;
  vector<mint> fac,finv,inv;
  // i!, 1/i!, 1/i

  // v = (v_0, v_1, ... , v_{n-1}) に対し
  // f(x) = sum_i ( n-1-i+xCx v_i ) とする
  // {f(0), f(1), ... , f(m-1)} を返す
  vector<mint> enumerate_f(int _n,vector<mint> &v,int m){
    vector<mint> _v=v;
    reverse(all(_v));
    rep(i,0,_n){
      _v[i]*=finv[i];
    }
    reverse(all(_v));
    // _v = (v_{0}/(n-1)!, v_{1}/(n-2)!, ... , v_{n-1}/0!)

    vector<mint> fsub(_n+m);
    rep(i,0,_n+m){
      fsub[i]=fac[i];
    }

    vector<mint> f=convolution(_v,fsub),res;
    rep(i,0,m){
      res.emplace_back(f[_n-1+i]*finv[i]);
    }
    return res;
  }

  // v = (v_0, v_1, ... , v_{n-1}), l に対し
  // g(x) = sum_i ( l-i+xCl v_i ) とする
  // {g(0), g(1), ... , g(n-1)} を返す
  vector<mint> enumerate_g(int _n,vector<mint> &v,int l){
    vector<mint> _v=v;

    vector<mint> gsub(_n-1,0);
    rep(i,0,_n){
      gsub.emplace_back(fac[l+i]*finv[i]);
    }

    vector<mint> g=convolution(_v,gsub),res;
    rep(i,0,_n){
      res.emplace_back(g[_n-1+i]*finv[l]);
    }
    return res;
  }

  /*
  // 長さ _n の(広義単調増加な)非負整数列 _a に対し以下を考える
  // 横の長さを _n とする辺がある 左から i の地点から _a[i] だけ上に伸びる辺がある
  // 上手い具合に横線が引いてある
  // また下辺の左から i の地点には start[i] が書かれている
  // この状態でマス目数え上げ DP をしたとき、一番右の辺に書かれた数字 _a[_n-1] 個を返す
  vector<mint> sub(int _n,vector<int> &_a,vector<mint> &start){
    int m=_a[_n-1];
    vector<mint> res(m+1);
    
    if(_n==1){
      rep(i,0,m+1){
        res[i]=start[0];
      }
      return res;
    }
    if(_n==2){
      rep(i,0,m+1){
        res[i]=start[0]*min((int)i+1,_a[0]+1)+start[1];
      }
      return res;
    }

    // _n >= 3
    int mid=_n/2;
    int m_front=_a[mid];
    vector<int> _a_front(mid+1),_a_back(_n-mid);
    vector<mint> start_front(mid+1),start_end(_n-mid,0);
    
    rep(i,0,mid+1){
      _a_front[i]=_a[i];
      start_front[i]=start[i];
      if(i==mid)start_front[i]=0;
    }

    rep(i,mid,_n){
      _a_back[i-mid]=_a[i]-m_front;
      start_end[i-mid]=start[i];
    }

    vector<mint> sub_front=sub(mid+1,_a_front,start_front);
    // sub_front は長さ m_front+1

    per(i,m_front,1){
      sub_front[i]-=sub_front[i-1];
    }
    per(i,_n-mid,1){
      start_end[i]-=start_end[i-1];
    }

    vector<mint> sub_front_f=enumerate_f(m_front+1,sub_front,_n-mid);
    vector<mint> sub_front_g=enumerate_g(m_front+1,sub_front,_n-mid-1);

    vector<mint> start_end_f=enumerate_f(_n-mid,start_end,m_front+1);
    vector<mint> start_end_g=enumerate_g(_n-mid,start_end,m_front);

    rep(i,0,m_front){
      res[i]=sub_front_g[i]+start_end_f[i];
    }

    rep(i,0,_n-mid+1){
      start_end[i]=sub_front_f[i]+start_end_g[i];
    }

    start_end[0]=0;

    vector<mint> sub_end=sub(_n-mid,_a_back,start_end);

    rep(i,0,(int)sub_end.size()){
      res[i+m_front]=sub_end[i];
    }

    return res;
  }
  */

  // 長さ _n の(広義単調増加な)非負整数列 _a に対し以下を考える
  // 横の長さを _n とする辺がある 左から i の地点から _a[i] だけ上に伸びる辺がある
  // 上手い具合に横線が引いてある
  // また下辺の左から i の地点には start[i] が書かれている
  // この状態でマス目数え上げ DP をしたとき、一番右の辺に書かれた数字 _a[_n-1] 個を返す
  vector<mint> sub(int _n,vector<int> &_a,vector<mint> &start){
    int m=_a[_n-1];
    vector<mint> res(m+1);
    
    if(_n==1){
      rep(i,0,m+1){
        res[i]=start[0];
      }
      return res;
    }
    if(_n==2){
      rep(i,0,m+1){
        res[i]=start[0]*min((int)i+1,_a[0]+1)+start[1];
      }
      return res;
    }

    // _n >= 2
    int mid=_n/2;
    int m_front=_a[mid];
    vector<int> _a_front(mid+1),_a_back(_n-mid);
    vector<mint> start_front(mid+1),start_end(_n-mid,0);
    
    rep(i,0,mid+1){
      _a_front[i]=_a[i];
      start_front[i]=start[i];
      if(i==mid)start_front[i]=0;
    }

    rep(i,mid,_n){
      _a_back[i-mid]=_a[i]-m_front;
      start_end[i-mid]=start[i];
    }

    vector<mint> sub_front=sub(mid+1,_a_front,start_front);
    // sub_front は長さ m_front+1

    per(i,m_front,1){
      sub_front[i]-=sub_front[i-1];
    }
    /*per(i,_n-mid,1){
      start_end[i]-=start_end[i-1];
    }*/

    vector<mint> sub_front_f=enumerate_f(m_front+1,sub_front,_n-mid);
    vector<mint> sub_front_g=enumerate_g(m_front+1,sub_front,_n-mid-1);

    vector<mint> start_end_f=enumerate_f(_n-mid,start_end,m_front+1);
    vector<mint> start_end_g=enumerate_g(_n-mid,start_end,m_front);

    rep(i,0,m_front){
      res[i]=sub_front_g[i]+start_end_f[i];
    }

    rep(i,0,_n-mid){
      start_end[i]=sub_front_f[i]+start_end_g[i];
    }

    per(i,_n-mid-1,1){
      start_end[i]-=start_end[i-1];
    }

    vector<mint> sub_end=sub(_n-mid,_a_back,start_end);


    rep(i,0,(int)sub_end.size()){
      res[i+m_front]=sub_end[i];
    }

    return res;
  }

public:
  number_of_increasing_sequences_between_two_sequences() = default;
  number_of_increasing_sequences_between_two_sequences(int _n,vector<int> _a,vector<int> _b){
    n=_n;
    a=_a;
    b=_b;

    rep(i,0,n){
      if(a[i]>b[i])zelo_flg=1;
      if(i>0&&b[i]<a[i-1])zelo_flg=1;
    }

    per(i,n-2,0){
      b[i]=min(b[i],b[i+1]);
    }

    rep(i,1,n){
      a[i]=max(a[i],a[i-1]);
    }

    int al=a[n-1],bl=b[n-1];

    per(i,n-1,1){
      a[i]=min(a[i],a[i-1]);
    }

    int dec=a[0];
    rep(i,0,n)a[i]-=dec;
    rep(i,0,n)b[i]-=dec;

    n++;
    a.emplace_back(al-dec);
    b.emplace_back(bl+5-dec);

    rep(i,0,n){
      if(a[i]>b[i])zelo_flg=1;
      if(i>0&&b[i]<a[i-1])zelo_flg=1;
    }

    int m=max((n+max(a[n-1],b[n-1]))*2+10,100);
    fac.resize(m);
    finv.resize(m);
    inv.resize(m);
    fac[0]=fac[1]=1;
    finv[0]=finv[1]=1;
    inv[1]=1;
    rep(i,2,m){
      fac[i]=fac[i-1]*i;
      inv[i]=-inv[mod%i]*(mod/i);
      finv[i]=finv[i-1]*inv[i];
    }
  }
  
  void debug_a(){
    for(int val:a)cout<<val<<" ";
    cout<<endl;
  }
  
  void debug_b(){
    for(int val:b)cout<<val<<" ";
    cout<<endl;
  }
  
  // 以下を満たす "広義" 単調増加の整数列 x の個数を返す
  // a_i <= x_i <= b_i
  mint answer(){
    if(zelo_flg)return 0;
    if(n==1){
      return (mint)b[0]-a[0]+1;
    }
    

    int dist=upper_bound(all(a),a[0])-a.begin();
    // [0,dist) までは a_i = a_0

    int px=0,py=a[0];
    int qx=dist-1,qy=a[0];
    if(qx==0){
      qy=b[0];
    }

    vector<mint> now(abs(qx-px)+abs(qy-py)+1,0);
    now[0]=1;

    while(qx!=n-1||qy!=b[n-1]){
      // cout<<"# "<<px<<" "<<py<<" "<<qx<<" "<<qy<<endl;
      int sz=now.size();
      per(i,sz-1,1){
        if(i==1&&px==0&&py==0)break;
        now[i]-=now[i-1];
      }

      /*rep(i,0,sz)cout<<now[i].val()<<" ";
      cout<<endl;*/

      if(py==qy){
        // 上に伸ばす
        vector<int> _a(qx-px+1);
        rep(i,0,qx-px+1){
          _a[i]=b[px+i]-py;
          //if(i<qx-px-1)_a[i]++;
        }
        /*cout<<" ? ";
        rep(i,0,qx-px+1){
          cout<<_a[i]<<" ";
        }
        cout<<endl;*/
        now=sub(qx-px+1,_a,now);
        px=qx,py=qy;
        qy=b[qx];
      }
      else{
        // 右に伸ばす
        int index=upper_bound(all(a),qy)-a.begin();
        // (px,py), (qx=px,qy) ->
        // (qx,qy), (index,qy)
        vector<int> _a(qy-py+1);
        rep(i,0,qy-py+1){
          int index2=upper_bound(all(a),py+i)-a.begin();
          _a[i]=index2-px;
          //if(i<qy-py-1)_a[i]++;
        }
        per(i,qy-py,0)_a[i]-=_a[0];
        
        /*cout<<" ! ";
        rep(i,0,qy-py+1){
          cout<<_a[i]<<" ";
        }
        cout<<endl;*/

        now=sub(qy-py+1,_a,now);
        px=qx,py=qy;
        qx=index-1;
      }
    }

    /*cout<<" ## ";
    rep(i,0,now.size()){
      cout<<now[i].val()<<" ";
    }
    cout<<endl;*/

    return now[now.size()-1];
  }
};

using ll = long long;

#define rep(i,start,end) for(ll i=start;i<(ll)(end);i++)

using mint = modint998244353;

/*
mint naive(int n,vector<int> a,vector<int> b){
  int mx=3000;
  mint dp[n][mx]={};
  rep(i,a[0],b[0]+1){
    dp[0][i]=1;
  }
  rep(i,1,n){
    rep(j,a[i],b[i]+1){
      rep(k,0,mx){
        if(j<k)break;
        dp[i][j]+=dp[i-1][k];
      }
      //cout<<i<<" , "<<j<<" : "<<dp[i][j].val()<<endl;
    }
  }
  mint res=0;
  rep(i,0,mx){
    res+=dp[n-1][i];
  }
  return res;
}
*/

int main(){
  int n,m;
  scanf("%d %d", &n, &m);
  // cin>>n>>m;
  vector<int> a(n),b(n);
  rep(i,0,n)scanf("%d", &a[i]);
  rep(i,0,n)scanf("%d", &b[i]);
  // rep(i,0,n)cin>>a[i];
  // rep(i,0,n)cin>>b[i];
  rep(i,0,n)b[i]--;
  number_of_increasing_sequences_between_two_sequences num(n,a,b);
  // num.debug_a();
  // num.debug_b();
  // cout<<endl;
  printf("%d\n",num.answer().val());
  // cout<<num.answer().val()<<endl;
  // cout<<naive(n,a,b).val()<<endl;
}