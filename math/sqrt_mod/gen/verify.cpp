#include <algorithm>
#include "testlib.h"

using namespace std;

bool is_prime(long long x) {
    if (x <= 1) return false;
    for (long long i = 2; i * i <= x; i++) {
        if (x % i == 0) return false;
    }
    return true;
}

template<class T, class U>
T pow_mod(T x, U n, T md) {
    T r = 1 % md;
    x %= md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

int main() {
    registerValidation();

    int t = inf.readInt(1, 100'000);
    inf.readEoln();

    for (int i = 0; i < t; i++) {
        long long y = inf.readLong(0LL, 1'000'000'000LL);
        inf.readSpace();
        long long p = inf.readLong(2LL, 1'000'000'000LL);
        inf.readEoln();
        ensure(y <= p);
        ensure(is_prime(p));
    }    
    inf.readEof();
}
