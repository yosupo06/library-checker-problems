#include <cstdint>
#include <cassert>
#include <limits>
#include "random.h"

// using u64 = std::int64_t;
using u64 = std::uint64_t;

// x * y mod m
u64 modprod(u64 x, u64 y, u64 m) {
    assert(m <= std::numeric_limits<u64>::max());

    x %= m;
    y %= m;

    if(m <= std::numeric_limits<u64>::max() / m) {
        return x * y % m;
    }

    u64 res = 0, crt = x;
    while(0 < y) {
        if(y & 1) {
            res += crt;
            if(m <= res) {
                res -= m;
            }
        }
        crt *= 2;
        if(m <= crt) {
            crt -= m;
        }
        y /= 2;
    }
    return res;
}

// x ** y mod m
// 0 ** 0 = 1
u64 modpow(u64 x, u64 y, u64 m) {
    x %= m;
    u64 res = 1, crt = x;
    while(0 < y) {
        if(y & 1) {
            res = modprod(res, crt, m);
        }
        crt = modprod(crt, crt, m);
        y /= 2;
    }
    return res;
}

// determine if x is prime.
bool miller_rabin(u64 p) {
    static const u64 witnesses[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    if(p == 1 || p % 2 == 0) {
        return p == 2;
    }
    
    // p - 1 = 2 ** r * d
    u64 r = 0, d = p - 1;
    while(d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    for(u64 wt: witnesses) {
        if(wt % p == 0) {
            continue;
        }
        u64 y = modpow(wt, d, p);
        if(y == 1 || y == p - 1) {
            continue;
        }
        for(u64 c = 0; c < r; c++) {
            y = modprod(y, y, p);
            if(y == p - 1) {
                break;
            }
        }
        if(y != p - 1) {
            return false;
        }
    }

    return true;
}

bool is_prime(u64 n) {
    int primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    for(int p : primes) {
        if(n % p == 0) {
            return false;
        }
    }
    return miller_rabin(n);
}

class PrimeGenerator {
    static const std::size_t M_LEN = 8;
    static const std::size_t D     = 30;
    static const int M[M_LEN];

    size_t idx;

    public:
    PrimeGenerator() : idx(0) {}

    // WARNIG: this method doesn't generate prime uniformly.
    u64 gen(u64 upper, Random &gen) {
        u64 gen_upper = upper / D;
        assert(1 < gen_upper);
        gen_upper--;
        u64 res;
        do {
            res = gen.uniform<u64>(0, gen_upper) * D + M[idx];
            idx = (idx == M_LEN - 1) ? 0 : idx + 1;
        } while(!miller_rabin(res));
        return res;
    }
};

const int PrimeGenerator::M[8] = {1, 7, 11, 13, 17, 19, 23, 29};
