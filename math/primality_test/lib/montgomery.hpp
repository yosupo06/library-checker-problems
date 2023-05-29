#ifndef MONTGOMERY_HPP
#define MONTGOMERY_HPP

#include <utility>
#include "util.hpp"

class MontgomeryGenerator;

class Montgomery {
    private:

    static const u64 MASK64 = ~0;
    static const u64 MASK32 = (1LL << 32) - 1;

    u64 MOD;
    u64 INV; // = (-MOD)^(-1) mod 2^64
    u64 v;

    // a * b = res.first * 2^64 + res.second
    std::pair<u64, u64> mul(u64 a, u64 b) const {
        u64 a1  = a >> 32,
            a2  = a & MASK32,
            b1  = b >> 32,
            b2  = b & MASK32,
            c11 = a1 * b1,
            c12 = a1 * b2,
            c21 = a2 * b1,
            c22 = a2 * b2;
        u64 carry = ((c22 >> 32) + (c12 & MASK32) + (c21 & MASK32)) >> 32;
        return std::make_pair(
            c11 + (c12 >> 32) + (c21 >> 32) + carry,
            (c12 << 32) + (c21 << 32) + c22
        );
    }

    // x * (2^64)^-1 mod MOD
    u64 reduce(u64 x2) const {
        if(x2 == 0) return 0;
        u64 b = x2 * INV;
        // (x + MOD * b) / 2^64
        auto y = mul(MOD, b);
        return y.first + 1;
    }

    // (x1 * 2^64 + x2) * (2^64)^-1 mod MOD
    u64 reduce(u64 x1, u64 x2) const {
        if(x2 == 0) return x1;
        u64 b = x2 * INV;
        // (x + MOD * b) / 2^64
        auto res = mul(MOD, b).first + x1 + 1;
        if(MOD <= res) res -= MOD;
        return res;
    }

    Montgomery make_montgomery(u64 x) {
        return Montgomery(MOD, INV, x);
    }

    Montgomery(u64 mod, u64 inv, u64 x) : MOD(mod), INV(inv), v(modprod(x, (~MOD) + 1, MOD)) {
        assert(mod < (1ULL << 63));
    }

    public:

    u64 val() const {
        return reduce(v);
    }

    Montgomery pow(u64 k) {
        Montgomery now = *this, ret = make_montgomery(1);
        while(k) {
            if(k % 2 == 1) {
                ret = ret * now;
            }
            k /= 2;
            now = now * now;
        }
        return ret;
    }

    Montgomery operator*(const Montgomery &lhs) const {
        assert(MOD == lhs.MOD);
        auto tmp = mul(v, lhs.v);
        auto res = *this;
        res.v = reduce(tmp.first, tmp.second);
        return res;
    }

    friend class MontgomeryGenerator;
};

class MontgomeryGenerator {
    private:
    const u64 MOD;
    const u64 INV; // = (-MOD)^(-1) mod 2^64

    u64 calc_inv() {
        u64 res = 0,
            t   = 0,
            i   = 1;
        for(int j = 0; j < 64; j++) {
            if(t % 2 == 0) {
                t += MOD;
                res += i;
            }
            t /= 2;
            i *= 2;
        }
        return res;
    }

    public:
    MontgomeryGenerator(u64 m) : MOD(m), INV(calc_inv()) {}

    Montgomery gen(u64 x) const {
        return Montgomery(MOD, INV, x);
    }
};

#endif // MONTGOMERY_HPP
