#include <iostream>
#pragma GCC target("pclmul")
#include <immintrin.h>

#include <algorithm>
#include <array>
#include <cassert>
#include <cstdint>
#include <cstring>
#include <random>
#include <type_traits>
#include <vector>
// #include <span>

// #pragma once

namespace my {

template <typename T>
class span {
   public:
    span() : m_ptr(nullptr), m_size(0) { ; }
    span(T* beg, T* end) : m_ptr(beg), m_size(end - beg) { ; }
    span(T* beg, size_t cnt) : m_ptr(beg), m_size(cnt) { ; }
    span(std::vector<T>& vec) : span(vec.data(), vec.size()) { ; }

    span(typename std::vector<T>::iterator beg, typename std::vector<T>::iterator end) : m_ptr(0), m_size(0) {
        if (beg != end) {
            m_ptr = &*beg, m_size = end - beg;
        }
    }

    span subspan(size_t beg, size_t cnt = 1e18) const {
        return span(m_ptr + beg, m_ptr + std::min(beg + cnt, m_size));
    }

    T& operator[](size_t ind) const { return m_ptr[ind]; }
    T* begin() const { return m_ptr; }
    T* end() const { return m_ptr + m_size; }

    size_t size() const { return m_size; }

   private:
    T* m_ptr;
    size_t m_size;
};

};  // namespace my

using my::span;

namespace Field_64 {

using u64 = uint64_t;
using u128 = __uint128_t;

__m128i clmul_vec(u64 a, u64 b) {
    __m128i tmp = _mm_clmulepi64_si128(_mm_cvtsi64_si128(a), _mm_cvtsi64_si128(b), 0);
    return tmp;
}

u128 clmul(u64 a, u64 b) {
    __m128i tmp = clmul_vec(a, b);
    u128 res;
    memcpy(&res, &tmp, 16);
    return res;
}

constexpr u128 clmul_constexpr(u64 a, u64 b) {
    u128 res = 0;
    for (int i = 0; i < 64; i++) {
        if (a >> i & 1) {
            res ^= u128(b) << i;
        }
    }
    return res;
}

int lg_u128(u128 val) {
    u64 a = val, b = val >> 64;
    return b ? 64 + (63 - __builtin_clzll(b)) : (a ? 63 - __builtin_clzll(a) : -1);
}

u128 take_mod(u128 val, u128 mod) {
    int lg = lg_u128(mod);
    for (int i = lg_u128(val); i >= lg; i = lg_u128(val)) {
        val ^= mod << (i - lg);
    }
    return val;
}

u128 pow_mod(u128 b, u128 exp, u128 mod) {
    assert(lg_u128(mod) <= 64);
    u128 r = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) {
            r = take_mod(clmul(r, b), mod);
        }
        b = take_mod(clmul(b, b), mod);
    }
    return r;
}

u128 poly_gcd(u128 a, u128 b) {
    while (b) {
        a = take_mod(a, b), std::swap(a, b);
    }
    return a;
}

bool is_irreducible_naive(u128 mod) {
    int lg = lg_u128(mod);
    for (u128 i = 2; i < (u128(1) << (lg / 2 + 1)) && i < mod; i++) {
        if (take_mod(mod, i) == 0) {
            return false;
        }
    }
    return true;
}

bool is_irreducible(u128 mod) {
    const int n = lg_u128(mod);
    auto get = [&](int k) {
        return take_mod(pow_mod(2, u128(1) << k, mod) ^ 2, mod);
    };
    bool result = true;
    if (poly_gcd(get(n), mod) != mod) {
        result = false;
    } else {
        for (int i = 1; i < n; i++) {
            if (n % i == 0 && poly_gcd(get(i), mod) != 1) {
                result = false;
                break;
            }
        }
    }
    // if (result != is_irreducible_naive(mod)) {
    //     std::cerr << result << " " << (u64)mod << "\n";
    // }
    // assert(result == is_irreducible_naive(mod));
    return result;
}

// std::mt19937_64 rnd_64;

u128 find_irreducible_poly(int deg) {
    // while (true) {
    //     u128 mod = rnd_64() | u128(rnd_64()) << 64;
    //     mod >>= 127 - deg;
    //     mod |= u128(1) << deg;
    //     if (is_irreducible(mod)) {
    //         return mod;
    //     }
    // }
    for (u128 mod = u128(1) << deg; (mod >> (deg + 1)) == 0; mod++) {
        if (is_irreducible(mod)) {
            return mod;
        }
    }
    assert(false);
}

namespace aux {
static constexpr u128 mod = 0b11011 | u128(1) << 64;

static constexpr u64 inv = [] {
    auto clmul = clmul_constexpr;
    u64 a = 1;
    for (int i = 0; i < 6; i++) {
        a = clmul(a, clmul(a, (u64)mod));
    }
    return a;
}();
static constexpr auto pow = [](int exp) {
    u128 r = 1;
    for (int i = 0; i < exp; i++) {
        r <<= 1;
        if (r >> 64 & 1) {
            r ^= mod;
        }
    }
    return (u64)r;
};

static constexpr u64 r = pow(64);
static constexpr u64 r2 = pow(128);

static_assert((u64)clmul_constexpr(u64(mod), inv) == 1);

}  // namespace aux

using namespace aux;

struct Field {
   public:
    static u64 reduce(u128 val) {
        u64 f = clmul(val, inv);
        // return (val ^ clmul(f, (u64)mod) ^ u128(f) << 64) >> 64;
        return val >> 64 ^ clmul(f, (u64)mod) >> 64 ^ f;
    }

    // private:
   public:
    u64 val;

   public:
    Field(u64 val, int) : val(val) { ; }

   public:
    explicit Field() : val(0) { ; }
    explicit Field(u64 val) : val(reduce(clmul(val, r2))) { ; }

    static Field n(int64_t n) { return Field(n & 1); }

    Field operator-() const { return Field() - *this; }
    Field& operator+=(const Field& other) { return val ^= other.val, *this; }
    Field& operator-=(const Field& other) { return val ^= other.val, *this; }
    Field& operator*=(const Field& other) {
        val = reduce(clmul(val, other.val));
        return *this;
    }

    friend Field operator+(Field a, Field b) { return a += b; }
    friend Field operator-(Field a, Field b) { return a -= b; }
    friend Field operator*(Field a, Field b) { return a *= b; }

    Field power(u64 exp) const {
        Field r = n(1);
        Field b = *this;
        for (; exp; exp >>= 1) {
            if (exp & 1) r *= b;
            b *= b;
        }
        return r;
    }

    Field inverse() const {
        Field res = power(~u64() - 1);
        assert(res * *this == n(1));
        return res;
    }

    // u64 get() const { return val; }
    u64 get() const { return reduce(val); }

    bool operator==(const Field& other) const { return val == other.val; }
    bool operator!=(const Field& other) const { return val != other.val; }

    // friend std::ostream& operator<<(std::ostream& out, const Field& val) { return out << val.val; }
};

};  // namespace Field_64

namespace conv {

using F = Field_64::Field;

template <typename R>
std::vector<R> convolve_naive(const std::vector<R>& a, const std::vector<R>& b) {
    if (a.empty() || b.empty()) {
        return {};
    }
    using namespace Field_64;
    if constexpr (std::is_same_v<R, Field>) {
        size_t sz = a.size() + b.size() - 1;
        __m128i* ptr = (__m128i*)_mm_malloc(16 * sz, 16);
        memset(ptr, 0, 16 * sz);

        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < b.size(); j++) {
                ptr[i + j] ^= clmul_vec(a[i].val, b[j].val);
            }
        }

        std::vector<R> c(sz);
        for (size_t i = 0; i < sz; i++) {
            c[i] = R(R::reduce((u128)ptr[i]), 0);
        }
        _mm_free(ptr);
        return c;
    } else {
        std::vector<R> c(a.size() + b.size() - 1);
        for (size_t i = 0; i < a.size(); i++) {
            for (size_t j = 0; j < b.size(); j++) {
                c[i + j] += a[i] * b[j];
            }
        }
        return c;
    }
}

std::vector<F> gen(std::vector<F> bs) {
    int lg = bs.size();
    std::vector<F> G(1 << lg);
    G[0] = F();
    for (int k = 0; k < lg; k++) {
        for (int i = 0; i < (1 << k); i++) {
            G[(1 << k) + i] = G[i] + bs[k];
        }
    }
    return G;
}

struct FFT {
    struct Data {
        std::vector<F> bt, gm, dt;
        std::vector<F> G;

        std::vector<F> pw, pw_inv;

        F bt_m_inv;

        mutable std::vector<F> aux;

        void init() {
            int lg = bt.size();

            aux.resize(1 << lg);

            F b = bt.back(), b_inv = bt.back().inverse();

            gm.assign(lg - 1, F());
            for (int i = 0; i < lg - 1; i++) {
                gm[i] = bt[i] * b_inv;
            }
            dt.assign(lg - 1, F());
            for (int i = 0; i < lg - 1; i++) {
                dt[i] = gm[i] * gm[i] + gm[i];
            }

            G = gen(gm);

            pw.assign(1 << lg, F());
            pw_inv.assign(1 << lg, F());
            F x = F::n(1), y = F::n(1);
            for (int i = 0; i < (1 << lg); i++, x *= b, y *= b_inv) {
                pw[i] = x, pw_inv[i] = y;
            }
            bt_m_inv = b_inv;
        }
    };

    std::vector<Data> data;

    void prepare(int lg) {
        if ((int)data.size() > lg) {
            return;
        }

        // data.resize(lg + 1);
        // data[lg].bt.resize(lg);
        // for (int i = 0; i < lg; i++) {
        //     data[lg].bt[i] = F(1 << i);
        // }
        // for (int k = lg; k > 0; k--) {
        //     data[k].init();
        //     data[k - 1].bt = data[k].dt;
        // }
        // return;

        {
            std::mt19937_64 rnd;
            std::vector<F> vec;
            while ((int)vec.size() < lg) {
                vec.clear();
                for (F x = F(rnd()); x != F(); x = x * x + x) {
                    vec.push_back(x);
                }
            }
            vec.erase(vec.begin(), vec.begin() + (vec.size() - lg));

            data.resize(lg + 1);
            data[lg].bt = vec;

            for (int k = lg; k > 0; k--) {
                data[k].init();
                data[k - 1].bt = data[k].dt;
            }
        }
    }
};

FFT fft_aux;

template <bool inverse = false>
// __attribute__((optimize("O3")))
// __attribute__((optimize("O3"), target("avx2")))
void taylor(span<F> f) {
    for (size_t n = inverse ? 1 : f.size() / 4; inverse ? n * 4 <= f.size() : n >= 1; inverse ? n *= 2 : n /= 2) {
        for (size_t t = 0; t < f.size(); t += 4 * n) {
            for (size_t i = 0; i < n; i++) {
                F b = f[t + 1 * n + i], c = f[t + 2 * n + i], d = f[t + 3 * n + i];
                f[t + 1 * n + i] = (inverse ? b + c : b + c + d), f[t + 2 * n + i] = c + d;
            }
        }
    }
}

template <bool inverse = false>
void fft(span<F> f) {
    if (f.size() == 1) {
        return;
    }
    size_t n = f.size();
    int lg = std::__lg(n);

    const FFT::Data& d = fft_aux.data[lg];

    // F bt_m_inv = d.bt_m_inv;
    const std::vector<F>& G = d.G;

    if (n == 2) {
        if (!inverse) {
            // f[1] = f[0] + f[1] * d.bt.back();
            f[1] = f[0] + f[1];
        } else {
            // f[1] = (f[0] + f[1]) * bt_m_inv;
            f[1] = f[0] + f[1];
        }
        return;
    }

    span<F> u(d.aux.begin(), d.aux.begin() + n / 2);
    span<F> v(d.aux.begin() + n / 2, d.aux.begin() + n);

    if (!inverse) {
        // if (d.bt.back() != F::n(1)) {
        //     for (size_t i = 0; i < n; i++) f[i] *= d.pw[i];
        // }

        taylor(f);

        for (size_t i = 0; i < n / 2; i++) {
            u[i] = f[2 * i], v[i] = f[2 * i + 1];
        }

        fft(u);
        fft(v);

        for (size_t i = 0; i < n / 2; i++) {
            F a = u[i] + G[i] * v[i];
            F b = a + v[i];

            f[i] = a, f[i + n / 2] = b;
        }
    } else {
        for (size_t i = 0; i < n / 2; i++) {
            F a = f[i], b = f[n / 2 + i];

            v[i] = a + b;
            u[i] = a + G[i] * v[i];
        }

        fft<true>(u);
        fft<true>(v);

        for (size_t i = 0; i < n / 2; i++) {
            f[2 * i] = u[i], f[2 * i + 1] = v[i];
        }

        taylor<true>(f);

        // if (d.bt.back() != F::n(1)) {
        //     for (size_t i = 0; i < n; i++) f[i] *= d.pw_inv[i];
        // }
    }
}

std::vector<F> convolve(std::vector<F> a, std::vector<F> b) {
    if (a.empty() || b.empty()) {
        return {};
    }

    size_t n = a.size(), m = b.size();
    int lg = 0;
    while ((1 << lg) < int64_t(n + m - 1)) lg++;

    if (int64_t(n * m) <= int64_t(1 << lg) * (lg + 1) * (lg + 1)) {
        return convolve_naive(a, b);
    }

    if (3 < lg && int64_t(n + m - 1) == (1 << (lg - 1)) + 1) {
        std::vector<F> dlt(m);
        for (size_t i = 0; i < m; i++) {
            dlt[i] = a.back() * b[i];
        }
        a.pop_back();
        std::vector<F> res = convolve(std::move(a), std::move(b));
        res.push_back(F());
        for (size_t i = 0; i < m; i++) {
            res[(n - 1) + i] += dlt[i];
        }
        return res;
    }

    fft_aux.prepare(lg);

    a.resize(1 << lg), b.resize(1 << lg);

    fft(a);
    fft(b);

    for (int i = 0; i < (1 << lg); i++) a[i] *= b[i];

    fft<true>(a);

    a.resize(n + m - 1);
    return a;
}

};  // namespace conv

using u64 = uint64_t;
using F = Field_64::Field;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);

    size_t n, m;
    std::cin >> n >> m;
    size_t k = n + m - 1;

    std::vector<F> a(n), b(m);
    for (auto& i : a) {
        u64 x;
        std::cin >> x;
        i = F(x);
    }
    for (auto& i : b) {
        u64 x;
        std::cin >> x;
        i = F(x);
    }

    std::vector<F> c = conv::convolve(a, b);
    assert(c.size() == k);

    for (size_t i = 0; i < k; i++) {
        std::cout << c[i].get() << " \n"[i + 1 == k];
    }

    return 0;
}
