#include "testlib.h"
#include "params.h"
#include <string>

using u128 = __uint128_t;

u128 parseU128(const std::string &s) {
    u128 res = 0;
    for (char c : s) {
        res = res * 10 + (c - '0');
    }
    return res;
}

int main() {
    registerValidation();
    int q = inf.readInt(1, MAX_Q, "Q");
    inf.readChar('\n');
    
    u128 max_n = parseU128(MAX_N);
    
    for (int i = 0; i < q; i++) {
        std::string s = inf.readToken("[1-9][0-9]*", "N");
        ensuref(s.length() <= 39, "N exceeds length bounds");
        u128 n = parseU128(s);
        ensuref(n >= 1 && n <= max_n, "N is out of bounds");
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
