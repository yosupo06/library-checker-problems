#include <cassert>
#include <cstdint>
#include <cstring>
#include <iostream>
#include <vector>

#pragma GCC target("pclmul")
#include <immintrin.h>

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

constexpr u128 mod = (u128(1) << 64) + 27;

u64 take_mod(u128 val) {
    for (int i = 127; i >= 64; i--) {
        if (val >> i & 1) {
            val ^= u128(mod) << (i - 64);
        }
    }
    assert(val < (u128(1) << 64));
    return (u64)val;
}

u64 mul_mod(u64 a, u64 b) {
    return take_mod(clmul(a, b));
}

int32_t main() {
    size_t n, m;
    std::cin >> n >> m;
    std::vector<u64> a(n), b(m);
    for (auto& i : a) std::cin >> i;
    for (auto& i : b) std::cin >> i;

    size_t k = n + m - 1;

    std::vector<u128> c(k);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            c[i + j] ^= clmul(a[i], b[j]);
        }
    }

    std::vector<u64> d(k);
    for (size_t i = 0; i < k; i++) {
        d[i] = take_mod(c[i]);
    }

    for (size_t i = 0; i < k; i++) {
        std::cout << d[i] << " \n"[i + 1 == k];
    }
}