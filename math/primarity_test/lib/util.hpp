#include <cstdint>
#include <cassert>
#include <limits>

using i64 = std::int64_t;

// x * y mod m
i64 modprod(i64 x, i64 y, i64 m) {
    assert(m <= std::numeric_limits<i64>::max());

    x %= m;
    y %= m;

    if(m <= std::numeric_limits<i64>::max() / m) {
        return x * y % m;
    }

    i64 res = 0, crt = x;
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
i64 modpow(i64 x, i64 y, i64 m) {
    x %= m;
    i64 res = 1, crt = x;
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
bool miller_rabin(i64 p) {
    static const i64 witnesses[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    if(p == 1 || p % 2 == 0) {
        return p == 2;
    }
    
    // p - 1 = 2 ** r * d
    i64 r = 0, d = p - 1;
    while(d % 2 == 0) {
        d /= 2;
        r++;
    }
    
    for(i64 wt: witnesses) {
        if(wt % p == 0) {
            continue;
        }
        i64 y = modpow(wt, d, p);
        if(y == 1 || y == p - 1) {
            continue;
        }
        for(i64 c = 0; c < r; c++) {
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

bool is_prime(i64 n) {
    return miller_rabin(n);
}
