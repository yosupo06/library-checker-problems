#include <iostream>
#include <string>
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

u128 rand128() {
    u128 a = rnd.next(1LL << 62);
    u128 b = rnd.next(1LL << 62);
    u128 c = rnd.next(1LL << 4);
    return (a << 66) | (b << 4) | c;
}

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    u128 max_n = parseU128(MAX_N);
    int q = MAX_Q;
    
    // Sometimes generate fewer cases
    if (rnd.next(0, 1) == 0) {
        q = rnd.next(1LL, (long long)MAX_Q);
    }
    
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        cout << rand128() % max_n + 1 << "\n";
    }
    
    return 0;
}
