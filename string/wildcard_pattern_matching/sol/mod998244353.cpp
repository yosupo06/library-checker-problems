#include <string>
#include <vector>
#include <tuple>
#include <iostream>

// ここから <atcoder/convolution> 展開
#include <algorithm>
#include <array>
#include <cassert>
#include <type_traits>
#include <vector>

#ifdef _MSC_VER
#include <intrin.h>
#endif

#if __cplusplus >= 202002L
#include <bit>
#endif

namespace atcoder
{

    namespace internal
    {

#if __cplusplus >= 202002L

        using std::bit_ceil;

#else

        unsigned int bit_ceil(unsigned int n)
        {
            unsigned int x = 1;
            while (x < (unsigned int)(n))
                x *= 2;
            return x;
        }

#endif

        int countr_zero(unsigned int n)
        {
#ifdef _MSC_VER
            unsigned long index;
            _BitScanForward(&index, n);
            return index;
#else
            return __builtin_ctz(n);
#endif
        }

        constexpr int countr_zero_constexpr(unsigned int n)
        {
            int x = 0;
            while (!(n & (1 << x)))
                x++;
            return x;
        }

    } // namespace internal

} // namespace atcoder

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

namespace atcoder
{

    namespace internal
    {

        constexpr long long safe_mod(long long x, long long m)
        {
            x %= m;
            if (x < 0)
                x += m;
            return x;
        }

        struct barrett
        {
            unsigned int _m;
            unsigned long long im;

            explicit barrett(unsigned int m) : _m(m), im((unsigned long long)(-1) / m + 1) {}

            unsigned int umod() const { return _m; }

            unsigned int mul(unsigned int a, unsigned int b) const
            {

                unsigned long long z = a;
                z *= b;
#ifdef _MSC_VER
                unsigned long long x;
                _umul128(z, im, &x);
#else
                unsigned long long x =
                    (unsigned long long)(((unsigned __int128)(z)*im) >> 64);
#endif
                unsigned long long y = x * _m;
                return (unsigned int)(z - y + (z < y ? _m : 0));
            }
        };

        constexpr long long pow_mod_constexpr(long long x, long long n, int m)
        {
            if (m == 1)
                return 0;
            unsigned int _m = (unsigned int)(m);
            unsigned long long r = 1;
            unsigned long long y = safe_mod(x, m);
            while (n)
            {
                if (n & 1)
                    r = (r * y) % _m;
                y = (y * y) % _m;
                n >>= 1;
            }
            return r;
        }

        constexpr bool is_prime_constexpr(int n)
        {
            if (n <= 1)
                return false;
            if (n == 2 || n == 7 || n == 61)
                return true;
            if (n % 2 == 0)
                return false;
            long long d = n - 1;
            while (d % 2 == 0)
                d /= 2;
            constexpr long long bases[3] = {2, 7, 61};
            for (long long a : bases)
            {
                long long t = d;
                long long y = pow_mod_constexpr(a, t, n);
                while (t != n - 1 && y != 1 && y != n - 1)
                {
                    y = y * y % n;
                    t <<= 1;
                }
                if (y != n - 1 && t % 2 == 0)
                {
                    return false;
                }
            }
            return true;
        }
        template <int n>
        constexpr bool is_prime = is_prime_constexpr(n);

        constexpr std::pair<long long, long long> inv_gcd(long long a, long long b)
        {
            a = safe_mod(a, b);
            if (a == 0)
                return {b, 0};

            long long s = b, t = a;
            long long m0 = 0, m1 = 1;

            while (t)
            {
                long long u = s / t;
                s -= t * u;
                m0 -= m1 * u; // |m1 * u| <= |m1| * s <= b

                auto tmp = s;
                s = t;
                t = tmp;
                tmp = m0;
                m0 = m1;
                m1 = tmp;
            }
            if (m0 < 0)
                m0 += b / s;
            return {s, m0};
        }

        constexpr int primitive_root_constexpr(int m)
        {
            if (m == 2)
                return 1;
            if (m == 167772161)
                return 3;
            if (m == 469762049)
                return 3;
            if (m == 754974721)
                return 11;
            if (m == 998244353)
                return 3;
            int divs[20] = {};
            divs[0] = 2;
            int cnt = 1;
            int x = (m - 1) / 2;
            while (x % 2 == 0)
                x /= 2;
            for (int i = 3; (long long)(i)*i <= x; i += 2)
            {
                if (x % i == 0)
                {
                    divs[cnt++] = i;
                    while (x % i == 0)
                    {
                        x /= i;
                    }
                }
            }
            if (x > 1)
            {
                divs[cnt++] = x;
            }
            for (int g = 2;; g++)
            {
                bool ok = true;
                for (int i = 0; i < cnt; i++)
                {
                    if (pow_mod_constexpr(g, (m - 1) / divs[i], m) == 1)
                    {
                        ok = false;
                        break;
                    }
                }
                if (ok)
                    return g;
            }
        }
        template <int m>
        constexpr int primitive_root = primitive_root_constexpr(m);

        unsigned long long floor_sum_unsigned(unsigned long long n,
                                              unsigned long long m,
                                              unsigned long long a,
                                              unsigned long long b)
        {
            unsigned long long ans = 0;
            while (true)
            {
                if (a >= m)
                {
                    ans += n * (n - 1) / 2 * (a / m);
                    a %= m;
                }
                if (b >= m)
                {
                    ans += n * (b / m);
                    b %= m;
                }

                unsigned long long y_max = a * n + b;
                if (y_max < m)
                    break;
                n = (unsigned long long)(y_max / m);
                b = (unsigned long long)(y_max % m);
                std::swap(m, a);
            }
            return ans;
        }

    } // namespace internal

} // namespace atcoder

#include <cassert>
#include <numeric>
#include <type_traits>

namespace atcoder
{

    namespace internal
    {

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

        template <class T>
        using is_integral = typename std::is_integral<T>;

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

        template <class T>
        using to_unsigned_t = typename to_unsigned<T>::type;

    } // namespace internal

} // namespace atcoder

namespace atcoder
{

    namespace internal
    {

        struct modint_base
        {
        };
        struct static_modint_base : modint_base
        {
        };

        template <class T>
        using is_modint = std::is_base_of<modint_base, T>;
        template <class T>
        using is_modint_t = std::enable_if_t<is_modint<T>::value>;

    } // namespace internal

    template <int m, std::enable_if_t<(1 <= m)> * = nullptr>
    struct static_modint : internal::static_modint_base
    {
        using mint = static_modint;

    public:
        static constexpr int mod() { return m; }
        static mint raw(int v)
        {
            mint x;
            x._v = v;
            return x;
        }

        static_modint() : _v(0) {}
        template <class T, internal::is_signed_int_t<T> * = nullptr>
        static_modint(T v)
        {
            long long x = (long long)(v % (long long)(umod()));
            if (x < 0)
                x += umod();
            _v = (unsigned int)(x);
        }
        template <class T, internal::is_unsigned_int_t<T> * = nullptr>
        static_modint(T v)
        {
            _v = (unsigned int)(v % umod());
        }

        unsigned int val() const { return _v; }

        mint &operator++()
        {
            _v++;
            if (_v == umod())
                _v = 0;
            return *this;
        }
        mint &operator--()
        {
            if (_v == 0)
                _v = umod();
            _v--;
            return *this;
        }
        mint operator++(int)
        {
            mint result = *this;
            ++*this;
            return result;
        }
        mint operator--(int)
        {
            mint result = *this;
            --*this;
            return result;
        }

        mint &operator+=(const mint &rhs)
        {
            _v += rhs._v;
            if (_v >= umod())
                _v -= umod();
            return *this;
        }
        mint &operator-=(const mint &rhs)
        {
            _v -= rhs._v;
            if (_v >= umod())
                _v += umod();
            return *this;
        }
        mint &operator*=(const mint &rhs)
        {
            unsigned long long z = _v;
            z *= rhs._v;
            _v = (unsigned int)(z % umod());
            return *this;
        }
        mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

        mint operator+() const { return *this; }
        mint operator-() const { return mint() - *this; }

        mint pow(long long n) const
        {
            assert(0 <= n);
            mint x = *this, r = 1;
            while (n)
            {
                if (n & 1)
                    r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        mint inv() const
        {
            if (prime)
            {
                assert(_v);
                return pow(umod() - 2);
            }
            else
            {
                auto eg = internal::inv_gcd(_v, m);
                assert(eg.first == 1);
                return eg.second;
            }
        }

        friend mint operator+(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) += rhs;
        }
        friend mint operator-(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) -= rhs;
        }
        friend mint operator*(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) *= rhs;
        }
        friend mint operator/(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) /= rhs;
        }
        friend bool operator==(const mint &lhs, const mint &rhs)
        {
            return lhs._v == rhs._v;
        }
        friend bool operator!=(const mint &lhs, const mint &rhs)
        {
            return lhs._v != rhs._v;
        }

    private:
        unsigned int _v;
        static constexpr unsigned int umod() { return m; }
        static constexpr bool prime = internal::is_prime<m>;
    };

    template <int id>
    struct dynamic_modint : internal::modint_base
    {
        using mint = dynamic_modint;

    public:
        static int mod() { return (int)(bt.umod()); }
        static void set_mod(int m)
        {
            assert(1 <= m);
            bt = internal::barrett(m);
        }
        static mint raw(int v)
        {
            mint x;
            x._v = v;
            return x;
        }

        dynamic_modint() : _v(0) {}
        template <class T, internal::is_signed_int_t<T> * = nullptr>
        dynamic_modint(T v)
        {
            long long x = (long long)(v % (long long)(mod()));
            if (x < 0)
                x += mod();
            _v = (unsigned int)(x);
        }
        template <class T, internal::is_unsigned_int_t<T> * = nullptr>
        dynamic_modint(T v)
        {
            _v = (unsigned int)(v % mod());
        }

        unsigned int val() const { return _v; }

        mint &operator++()
        {
            _v++;
            if (_v == umod())
                _v = 0;
            return *this;
        }
        mint &operator--()
        {
            if (_v == 0)
                _v = umod();
            _v--;
            return *this;
        }
        mint operator++(int)
        {
            mint result = *this;
            ++*this;
            return result;
        }
        mint operator--(int)
        {
            mint result = *this;
            --*this;
            return result;
        }

        mint &operator+=(const mint &rhs)
        {
            _v += rhs._v;
            if (_v >= umod())
                _v -= umod();
            return *this;
        }
        mint &operator-=(const mint &rhs)
        {
            _v += mod() - rhs._v;
            if (_v >= umod())
                _v -= umod();
            return *this;
        }
        mint &operator*=(const mint &rhs)
        {
            _v = bt.mul(_v, rhs._v);
            return *this;
        }
        mint &operator/=(const mint &rhs) { return *this = *this * rhs.inv(); }

        mint operator+() const { return *this; }
        mint operator-() const { return mint() - *this; }

        mint pow(long long n) const
        {
            assert(0 <= n);
            mint x = *this, r = 1;
            while (n)
            {
                if (n & 1)
                    r *= x;
                x *= x;
                n >>= 1;
            }
            return r;
        }
        mint inv() const
        {
            auto eg = internal::inv_gcd(_v, mod());
            assert(eg.first == 1);
            return eg.second;
        }

        friend mint operator+(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) += rhs;
        }
        friend mint operator-(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) -= rhs;
        }
        friend mint operator*(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) *= rhs;
        }
        friend mint operator/(const mint &lhs, const mint &rhs)
        {
            return mint(lhs) /= rhs;
        }
        friend bool operator==(const mint &lhs, const mint &rhs)
        {
            return lhs._v == rhs._v;
        }
        friend bool operator!=(const mint &lhs, const mint &rhs)
        {
            return lhs._v != rhs._v;
        }

    private:
        unsigned int _v;
        static internal::barrett bt;
        static unsigned int umod() { return bt.umod(); }
    };
    template <int id>
    internal::barrett dynamic_modint<id>::bt(998244353);

    using modint998244353 = static_modint<998244353>;
    using modint1000000007 = static_modint<1000000007>;
    using modint = dynamic_modint<-1>;

    namespace internal
    {

        template <class T>
        using is_static_modint = std::is_base_of<internal::static_modint_base, T>;

        template <class T>
        using is_static_modint_t = std::enable_if_t<is_static_modint<T>::value>;

        template <class>
        struct is_dynamic_modint : public std::false_type
        {
        };
        template <int id>
        struct is_dynamic_modint<dynamic_modint<id>> : public std::true_type
        {
        };

        template <class T>
        using is_dynamic_modint_t = std::enable_if_t<is_dynamic_modint<T>::value>;

    } // namespace internal

} // namespace atcoder

namespace atcoder
{

    namespace internal
    {

        template <class mint,
                  int g = internal::primitive_root<mint::mod()>,
                  internal::is_static_modint_t<mint> * = nullptr>
        struct fft_info
        {
            static constexpr int rank2 = countr_zero_constexpr(mint::mod() - 1);
            std::array<mint, rank2 + 1> root;  // root[i]^(2^i) == 1
            std::array<mint, rank2 + 1> iroot; // root[i] * iroot[i] == 1

            std::array<mint, std::max(0, rank2 - 2 + 1)> rate2;
            std::array<mint, std::max(0, rank2 - 2 + 1)> irate2;

            std::array<mint, std::max(0, rank2 - 3 + 1)> rate3;
            std::array<mint, std::max(0, rank2 - 3 + 1)> irate3;

            fft_info()
            {
                root[rank2] = mint(g).pow((mint::mod() - 1) >> rank2);
                iroot[rank2] = root[rank2].inv();
                for (int i = rank2 - 1; i >= 0; i--)
                {
                    root[i] = root[i + 1] * root[i + 1];
                    iroot[i] = iroot[i + 1] * iroot[i + 1];
                }

                {
                    mint prod = 1, iprod = 1;
                    for (int i = 0; i <= rank2 - 2; i++)
                    {
                        rate2[i] = root[i + 2] * prod;
                        irate2[i] = iroot[i + 2] * iprod;
                        prod *= iroot[i + 2];
                        iprod *= root[i + 2];
                    }
                }
                {
                    mint prod = 1, iprod = 1;
                    for (int i = 0; i <= rank2 - 3; i++)
                    {
                        rate3[i] = root[i + 3] * prod;
                        irate3[i] = iroot[i + 3] * iprod;
                        prod *= iroot[i + 3];
                        iprod *= root[i + 3];
                    }
                }
            }
        };

        template <class mint, internal::is_static_modint_t<mint> * = nullptr>
        void butterfly(std::vector<mint> &a)
        {
            int n = int(a.size());
            int h = internal::countr_zero((unsigned int)n);

            static const fft_info<mint> info;

            int len = 0; // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
            while (len < h)
            {
                if (h - len == 1)
                {
                    int p = 1 << (h - len - 1);
                    mint rot = 1;
                    for (int s = 0; s < (1 << len); s++)
                    {
                        int offset = s << (h - len);
                        for (int i = 0; i < p; i++)
                        {
                            auto l = a[i + offset];
                            auto r = a[i + offset + p] * rot;
                            a[i + offset] = l + r;
                            a[i + offset + p] = l - r;
                        }
                        if (s + 1 != (1 << len))
                            rot *= info.rate2[countr_zero(~(unsigned int)(s))];
                    }
                    len++;
                }
                else
                {
                    int p = 1 << (h - len - 2);
                    mint rot = 1, imag = info.root[2];
                    for (int s = 0; s < (1 << len); s++)
                    {
                        mint rot2 = rot * rot;
                        mint rot3 = rot2 * rot;
                        int offset = s << (h - len);
                        for (int i = 0; i < p; i++)
                        {
                            auto mod2 = 1ULL * mint::mod() * mint::mod();
                            auto a0 = 1ULL * a[i + offset].val();
                            auto a1 = 1ULL * a[i + offset + p].val() * rot.val();
                            auto a2 = 1ULL * a[i + offset + 2 * p].val() * rot2.val();
                            auto a3 = 1ULL * a[i + offset + 3 * p].val() * rot3.val();
                            auto a1na3imag =
                                1ULL * mint(a1 + mod2 - a3).val() * imag.val();
                            auto na2 = mod2 - a2;
                            a[i + offset] = a0 + a2 + a1 + a3;
                            a[i + offset + 1 * p] = a0 + a2 + (2 * mod2 - (a1 + a3));
                            a[i + offset + 2 * p] = a0 + na2 + a1na3imag;
                            a[i + offset + 3 * p] = a0 + na2 + (mod2 - a1na3imag);
                        }
                        if (s + 1 != (1 << len))
                            rot *= info.rate3[countr_zero(~(unsigned int)(s))];
                    }
                    len += 2;
                }
            }
        }

        template <class mint, internal::is_static_modint_t<mint> * = nullptr>
        void butterfly_inv(std::vector<mint> &a)
        {
            int n = int(a.size());
            int h = internal::countr_zero((unsigned int)n);

            static const fft_info<mint> info;

            int len = h; // a[i, i+(n>>len), i+2*(n>>len), ..] is transformed
            while (len)
            {
                if (len == 1)
                {
                    int p = 1 << (h - len);
                    mint irot = 1;
                    for (int s = 0; s < (1 << (len - 1)); s++)
                    {
                        int offset = s << (h - len + 1);
                        for (int i = 0; i < p; i++)
                        {
                            auto l = a[i + offset];
                            auto r = a[i + offset + p];
                            a[i + offset] = l + r;
                            a[i + offset + p] =
                                (unsigned long long)(mint::mod() + l.val() - r.val()) *
                                irot.val();
                            ;
                        }
                        if (s + 1 != (1 << (len - 1)))
                            irot *= info.irate2[countr_zero(~(unsigned int)(s))];
                    }
                    len--;
                }
                else
                {
                    int p = 1 << (h - len);
                    mint irot = 1, iimag = info.iroot[2];
                    for (int s = 0; s < (1 << (len - 2)); s++)
                    {
                        mint irot2 = irot * irot;
                        mint irot3 = irot2 * irot;
                        int offset = s << (h - len + 2);
                        for (int i = 0; i < p; i++)
                        {
                            auto a0 = 1ULL * a[i + offset + 0 * p].val();
                            auto a1 = 1ULL * a[i + offset + 1 * p].val();
                            auto a2 = 1ULL * a[i + offset + 2 * p].val();
                            auto a3 = 1ULL * a[i + offset + 3 * p].val();

                            auto a2na3iimag =
                                1ULL *
                                mint((mint::mod() + a2 - a3) * iimag.val()).val();

                            a[i + offset] = a0 + a1 + a2 + a3;
                            a[i + offset + 1 * p] =
                                (a0 + (mint::mod() - a1) + a2na3iimag) * irot.val();
                            a[i + offset + 2 * p] =
                                (a0 + a1 + (mint::mod() - a2) + (mint::mod() - a3)) *
                                irot2.val();
                            a[i + offset + 3 * p] =
                                (a0 + (mint::mod() - a1) + (mint::mod() - a2na3iimag)) *
                                irot3.val();
                        }
                        if (s + 1 != (1 << (len - 2)))
                            irot *= info.irate3[countr_zero(~(unsigned int)(s))];
                    }
                    len -= 2;
                }
            }
        }

        template <class mint, internal::is_static_modint_t<mint> * = nullptr>
        std::vector<mint> convolution_naive(const std::vector<mint> &a,
                                            const std::vector<mint> &b)
        {
            int n = int(a.size()), m = int(b.size());
            std::vector<mint> ans(n + m - 1);
            if (n < m)
            {
                for (int j = 0; j < m; j++)
                {
                    for (int i = 0; i < n; i++)
                    {
                        ans[i + j] += a[i] * b[j];
                    }
                }
            }
            else
            {
                for (int i = 0; i < n; i++)
                {
                    for (int j = 0; j < m; j++)
                    {
                        ans[i + j] += a[i] * b[j];
                    }
                }
            }
            return ans;
        }

        template <class mint, internal::is_static_modint_t<mint> * = nullptr>
        std::vector<mint> convolution_fft(std::vector<mint> a, std::vector<mint> b)
        {
            int n = int(a.size()), m = int(b.size());
            int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
            a.resize(z);
            internal::butterfly(a);
            b.resize(z);
            internal::butterfly(b);
            for (int i = 0; i < z; i++)
            {
                a[i] *= b[i];
            }
            internal::butterfly_inv(a);
            a.resize(n + m - 1);
            mint iz = mint(z).inv();
            for (int i = 0; i < n + m - 1; i++)
                a[i] *= iz;
            return a;
        }

    } // namespace internal

    template <class mint, internal::is_static_modint_t<mint> * = nullptr>
    std::vector<mint> convolution(std::vector<mint> &&a, std::vector<mint> &&b)
    {
        int n = int(a.size()), m = int(b.size());
        if (!n || !m)
            return {};

        int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
        assert((mint::mod() - 1) % z == 0);

        if (std::min(n, m) <= 60)
            return convolution_naive(a, b);
        return internal::convolution_fft(a, b);
    }
    template <class mint, internal::is_static_modint_t<mint> * = nullptr>
    std::vector<mint> convolution(const std::vector<mint> &a,
                                  const std::vector<mint> &b)
    {
        int n = int(a.size()), m = int(b.size());
        if (!n || !m)
            return {};

        int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
        assert((mint::mod() - 1) % z == 0);

        if (std::min(n, m) <= 60)
            return convolution_naive(a, b);
        return internal::convolution_fft(a, b);
    }

    template <unsigned int mod = 998244353,
              class T,
              std::enable_if_t<internal::is_integral<T>::value> * = nullptr>
    std::vector<T> convolution(const std::vector<T> &a, const std::vector<T> &b)
    {
        int n = int(a.size()), m = int(b.size());
        if (!n || !m)
            return {};

        using mint = static_modint<mod>;

        int z = (int)internal::bit_ceil((unsigned int)(n + m - 1));
        assert((mint::mod() - 1) % z == 0);

        std::vector<mint> a2(n), b2(m);
        for (int i = 0; i < n; i++)
        {
            a2[i] = mint(a[i]);
        }
        for (int i = 0; i < m; i++)
        {
            b2[i] = mint(b[i]);
        }
        auto c2 = convolution(std::move(a2), std::move(b2));
        std::vector<T> c(n + m - 1);
        for (int i = 0; i < n + m - 1; i++)
        {
            c[i] = c2[i].val();
        }
        return c;
    }

    std::vector<long long> convolution_ll(const std::vector<long long> &a,
                                          const std::vector<long long> &b)
    {
        int n = int(a.size()), m = int(b.size());
        if (!n || !m)
            return {};

        static constexpr unsigned long long MOD1 = 754974721; // 2^24
        static constexpr unsigned long long MOD2 = 167772161; // 2^25
        static constexpr unsigned long long MOD3 = 469762049; // 2^26
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

        static constexpr int MAX_AB_BIT = 24;
        static_assert(MOD1 % (1ull << MAX_AB_BIT) == 1, "MOD1 isn't enough to support an array length of 2^24.");
        static_assert(MOD2 % (1ull << MAX_AB_BIT) == 1, "MOD2 isn't enough to support an array length of 2^24.");
        static_assert(MOD3 % (1ull << MAX_AB_BIT) == 1, "MOD3 isn't enough to support an array length of 2^24.");
        assert(n + m - 1 <= (1 << MAX_AB_BIT));

        auto c1 = convolution<MOD1>(a, b);
        auto c2 = convolution<MOD2>(a, b);
        auto c3 = convolution<MOD3>(a, b);

        std::vector<long long> c(n + m - 1);
        for (int i = 0; i < n + m - 1; i++)
        {
            unsigned long long x = 0;
            x += (c1[i] * i1) % MOD1 * M2M3;
            x += (c2[i] * i2) % MOD2 * M1M3;
            x += (c3[i] * i3) % MOD3 * M1M2;
            long long diff =
                c1[i] - internal::safe_mod((long long)(x), (long long)(MOD1));
            if (diff < 0)
                diff += MOD1;
            static constexpr unsigned long long offset[5] = {
                0, 0, M1M2M3, 2 * M1M2M3, 3 * M1M2M3};
            x -= offset[diff % 5];
            c[i] = x;
        }

        return c;
    }

} // namespace atcoder
// ここまで <atcoder/convolution> 展開

using ll = long long;

static char buf[1 << 19];
std::string scan()
{
    scanf("%s", buf);
    return std::string(buf);
}

using mint = atcoder::modint998244353;

auto make_vectors(const std::string &s)
{
    size_t n = s.size();
    std::vector v(3, std::vector<mint>(n));
    for (size_t i = 0; i < n; i++)
    {
        ll a = s[i] == '*' ? 0 : s[i] - 'a' + 1;
        assert(0 <= a and a <= 26);
        v[0][i] = a;
        v[1][i] = a * a;
        v[2][i] = a * a * a;
    }
    return v;
}

int main()
{

    std::string s = scan();
    std::string t = scan();

    std::reverse(t.begin(), t.end());

    auto S = make_vectors(s);
    auto T = make_vectors(t);

    size_t n = s.size(), m = t.size();
    std::vector<mint> sum(n - m + 1, 0);
    for (size_t j = 0; j < 3; j++)
    {
        auto st = atcoder::convolution(S[j], T[2 - j]);
        for (size_t i = 0; i <= n - m; i++)
            if (j != 1)
                sum[i] += st[m - 1 + i];
            else
                sum[i] -= 2 * st[m - 1 + i];
    }

    for (auto a : sum)
        std::cout << !a.val();
    std::cout << "\n";
}