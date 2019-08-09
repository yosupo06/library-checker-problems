#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    long long x_ans = ans.readLong();
    long long x_ouf = ouf.readLong();

    if (x_ans != x_ouf) {
        quitf(_wa, "Value is differ - expected '%d', found '%d'", x_ans, x_ouf);
    }

    // input
    int n = inf.readInt();
    vector<vector<long long>> a(n, vector<long long>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = inf.readInt();
        }
    }

    long long sum = 0;
    set<int> used;
    for (int i = 0; i < n; i++) {
        int p = ouf.readLong();
        ensure(0 <= p && p < n);
        ensure(!used.count(p));
        used.insert(p);
        sum += a[i][p];
    }

    ensure(x_ouf == sum);
    quitf(_ok, "OK");
}
