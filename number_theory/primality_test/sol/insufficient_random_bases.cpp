#include <cinttypes>
#include <iostream>
#include "random.h"

auto gen = Random(0);

using u64 = uint64_t;
using u128 = __uint128_t;

u128 pow_mod(u128 b, u128 exp, u128 mod) {
    u128 r = 1;
    for (; exp; exp >>= 1) {
        if (exp & 1) {
            r = r * b % mod;
        }
        b = b * b % mod;
    }
    return r;
}

bool miller_rabin(u64 p, int iterations) {
    if(p == 1 || p % 2 == 0) {
        return p == 2;
    }
    if(p == 3) {
        return true;
    }

    // p - 1 = 2 ** r * d
    u64 r = 0, d = p - 1;
    while(d % 2 == 0) {
        d /= 2;
        r++;
    }

    for(int i = 0; i < iterations; i++) {
        u64 wt = gen.uniform(u64(2), p-2);

        u64 y = pow_mod(wt, d, p);

        if(y == 1 || y == p - 1) {
            continue;
        }
        for(u64 c = 1; c < r; c++) {
            y = u128(y) * y % p;
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

int main() {
    int q;
    scanf("%d\n", &q);
    // Assuming 25% failure rate of each MR iteration
    // Assuming 100000 tests
    // This solution has a 22% chance of AC
    for(int i = 0; i < q; i++) {
        u64 n;
        scanf("%" PRIu64 "\n", &n);
        if(miller_rabin(n, 8)) {
            printf("Yes\n");
        } else {
            printf("No\n");
        }
    }
}
