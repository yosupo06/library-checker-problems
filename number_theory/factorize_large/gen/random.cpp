#include <iostream>
#include <string>
#include <chrono>
#include "testlib.h"
#include "../params.h"

using namespace std;
using u128 = __uint128_t;

ostream &operator<<(ostream &stream, u128 n) {
    if (n == 0) return stream.put('0');
    char buf[40];
    char *p = buf + 40;
    do {
        *--p = (char)('0' + (unsigned)(n % 10));
        n /= 10;
    } while (n);
    return stream.write(p, (buf + 40) - p);
}

u128 parseU128(const std::string &s) {
    u128 res = 0;
    for (char c : s) {
        res = res * 10 + (c - '0');
    }
    return res;
}

static u128 s = std::chrono::steady_clock::now().time_since_epoch().count();
static inline u128 rand128()
{
    /*
     * LCG formula: X = (a * X + c) mod 2^128
     * 'a' is a 128-bit multiplier with strong spectral properties.
     * 'c' is an odd increment, ensuring a full period of 2^128.
     * Overflow of u128 natively handles the modulo 2^128.
     */
    const u128 a = ((u128)0x2360ED051FC65DA4ULL << 64) | 0x4385DF649FCCF645ULL;
    const u128 c = ((u128)0x5851F42D4C957F2DULL << 64) | 0x14057B7EF767814FULL;
    
    s = s * a + c;
    
    return s;
}

int main(int argc, char* argv[]) 
{
    registerGen(argc, argv, 1);
    
    u128 maxN = parseU128(MAX_N);
    int q = MAX_Q;
    
    // Sometimes generate fewer cases
    if (rnd.next(0, 1) == 0) {
        q = rnd.next(1LL, (long long)MAX_Q);
    }
    
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        cout << rand128() % maxN + 1 << "\n";
    }
    
    return 0;
}
