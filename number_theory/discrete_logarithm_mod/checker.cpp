#include <algorithm>
#include <iostream>
#include <cassert>
#include "testlib.h"

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
template <class T> using V = vector<T>;

ll pow_mod(ll x, ll n, ll md) {
    ll r = 1 % md;
    x %= md;
    while (n) {
        if (n & 1) r = (r * x) % md;
        x = (x * x) % md;
        n >>= 1;
    }
    return r;
}

ll read_ans(ll x, ll y, ll m, InStream& stream) {
    ll k = stream.readLong(-1, m);
    if (k != -1 && pow_mod(x, k, m) != y) stream.quit(_wa, "x^k != y");
    return k;
}

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    int t = inf.readInt();
    for (int i = 0; i < t; i++) {
        ll x = inf.readLong();
        ll y = inf.readLong();
        ll m = inf.readLong();

        ll expect = read_ans(x, y, m, ans);
        ll actual = read_ans(x, y, m, ouf);

        // ok
        if (expect == actual) continue;

        if (expect != -1 && actual == -1) {
            quitf(_wa, "Participate can't find solution");
        }
        if (expect == -1 && actual != -1) {
            quitf(_fail, "Judge can't find solution, wow!");
        }
        if (actual < expect) {
            quitf(_fail, "Participate find more better solution!");
        }
        if (actual > expect) {
            quitf(_wa, "Participate can't find best solution");
        }
    }
    quitf(_ok, "OK");
}
