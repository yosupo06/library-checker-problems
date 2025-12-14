#include <cassert>
#include <cstdint>
#include <iostream>
#include <vector>

using u64 = uint64_t;
using u128 = __uint128_t;

constexpr u128 mod = (u128(1) << 64) + 27;

u128 clmul(u64 a, u64 b) {
    u128 res = 0;
    for (int i = 0; i < 64; i++) {
        if (a >> i & 1) {
            res ^= u128(b) << i;
        }
    }
    return res;
}

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

    std::vector<u64> c(k);

    for (size_t i = 0; i < n; i++) {
        for (size_t j = 0; j < m; j++) {
            c[i + j] ^= mul_mod(a[i], b[j]);
        }
    }

    for (size_t i = 0; i < k; i++) {
        std::cout << c[i] << " \n"[i + 1 == k];
    }
}