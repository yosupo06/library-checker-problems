#ifndef PRIME_HPP
#define PRIME_HPP

#include <numeric>
#include "util.hpp"
#include "montgomery.hpp"

// determine if x is prime.
bool miller_rabin(u64 p) {
    static const u64 witnesses[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    if(p == 1 || p % 2 == 0) {
        return p == 2;
    }

    MontgomeryGenerator mg(p);
    
    // p - 1 = 2 ** r * d
    u64 r = 0, d = p - 1;
    while(d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    for(u64 wt: witnesses) {
        if(std::gcd(wt, p) != 1) {
            continue;
        }

        Montgomery y = mg.gen(wt).pow(d);
        u64 v = y.val();

        if(v == 1 || v == p - 1) {
            continue;
        }
        for(u64 c = 0; c < r; c++) {
            y = y * y;
            v = y.val();
            if(v == p - 1) {
                break;
            }
        }
        if(v != p - 1) {
            return false;
        }
    }

    return true;
}

bool is_prime(u64 n) {
    u64 primes[] = {2, 3, 5, 7, 11, 13, 17, 19};
    for(u64 p : primes) {
        if(p == n) return true;
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

#endif // PRIME_HPP
