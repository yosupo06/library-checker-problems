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

int main(int argc, char* argv[]) {
    registerGen(argc, argv, 1);
    
    int q = MAX_Q;
    unsigned __int128 semiPrimes[]{
        9986998694074992619ULL,
        9501540829148808241ULL,
        1553381999513383757ULL,
        3352240630789220717ULL,
        7241617205978236309ULL,
        534022786545143537ULL,
    };
    
    cout << q << "\n";
    for (int i = 0; i < q; i++) {
        int x = rnd.next(0, 5);
        int y = rnd.next(0, 5);
        cout << semiPrimes[x] * semiPrimes[y] << "\n";
    }
    
    return 0;
}
