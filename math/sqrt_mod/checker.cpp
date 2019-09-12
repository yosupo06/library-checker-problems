#include <algorithm>
#include "testlib.h"

using namespace std;
using ll = long long;

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

bool is_prime(ll n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    ll d = n - 1;
    while (d % 2 == 0) d /= 2;
    for (ll a : {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37}) {
        if (n <= a) break;
        ll t = d;
        ll y = pow_mod<__int128_t>(a, t, n);  // over
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

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();

    for (int i = 0; i < t; i++) {
        long long y = inf.readLong();
        long long p = inf.readLong();
        long long x = ouf.readLong(-1, p - 1);
        if (x != -1 && x * x % p != y) {
            quitf(_wa, "invalid x");
        }
        bool actual = (x != -1);
        bool expected = (y == 0 || pow_mod(y, (p - 1) / 2, p) == 1);
        if (expected && !actual) {
            quitf(_wa, "you cann't find x");
        }
        if (!expected && actual) {
            quitf(_fail, "what happened???");
        }
    }
    quitf(_ok, "OK");
}
