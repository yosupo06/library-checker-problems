#ifndef UTIL_HPP
#define UTIL_HPP

#include <cstdint>
#include <cassert>
#include <limits>
#include "random.h"

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


#endif // UTIL_HPP
