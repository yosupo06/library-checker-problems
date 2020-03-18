#include <algorithm>
#include "params.h"
#include "testlib.h"

using namespace std;

template <class T, class U> T pow_mod(T x, U n, T md) {
    T r = 1 % md;
    x %= md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    long long d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (long long a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n <= a) break;
        long long t = d;
        long long y = pow_mod<__int128_t>(a, t, n);  // over
        while (t != n - 1 && y != 1 && y != n - 1) {
            y = __int128_t(y) * y % n;  // flow
            t <<= 1;
        }
        if (y != n - 1 && t % 2 == 0) {
            return false;
        }
    }
    return true;
}


int main() {
    registerValidation();

    int t = inf.readInt(1, (int)T_MAX);
    inf.readChar('\n');

    set<long long> trusted;
    for (int i = 0; i < t; i++) {
        long long k = inf.readLong(0LL, K_MAX);
        inf.readSpace();
        long long y = inf.readLong(0LL, P_MAX - 1LL);
        inf.readSpace();
        long long p = inf.readLong(2LL, P_MAX);
        inf.readChar('\n');
        ensure(0<=k&&k<=K_MAX);
        ensure(2<=p&&p<=P_MAX);
        ensure(y < p);
        ensure(trusted.count(p) || is_prime(p));
        trusted.insert(p);
    }
    inf.readEof();
}
