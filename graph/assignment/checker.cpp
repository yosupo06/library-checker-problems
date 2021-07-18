#include "testlib.h"

using namespace std;
using ll = long long;

ll read_ans(vector<vector<ll>> a, InStream& stream) {
    int n = int(a.size());
    ll x = stream.readLong();
    ll sum = 0;
    vector<bool> used(n);
    for (int i = 0; i < n; i++) {
        int p = stream.readInt(0, n - 1);
        if (used[p]) {
            stream.quitf(_wa, "reuse %d", p);
        }
        used[p] = true;
        sum += a[i][p];
    }
    if (x != sum) {
        stream.quitf(_wa, "x is different: " I64 "(x) vs " I64 "(actual)", x, sum);
    }
    return x;
}

int main(int argc, char *argv[]) {
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    // input
    int n = inf.readInt();
    vector<vector<ll>> a(n, vector<ll>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = inf.readInt();
        }
    }

    ll x_ans = read_ans(a, ans);
    ll x_ouf = read_ans(a, ouf);

    if (x_ans > x_ouf) {
        quitf(_fail, I64 " " I64 ": Participate find better answer....", x_ans, x_ouf);
    } else if (x_ans < x_ouf) {
        quitf(_wa, I64 " " I64 ": There is the better solution", x_ans, x_ouf);
    }
    quitf(_ok, "OK: " I64, x_ans);
}
