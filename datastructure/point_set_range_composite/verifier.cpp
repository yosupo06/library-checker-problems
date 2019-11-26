#include "testlib.h"

const int MOD = 998244353;

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 500'000, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(1, MOD - 1, "a_i");
        inf.readSpace();
        inf.readInt(0, MOD - 1, "b_i");
        inf.readEoln();
    }
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t == 0) {
            inf.readInt(0, n - 1, "p");
            inf.readSpace();
            inf.readInt(1, MOD - 1, "c");
            inf.readSpace();
            inf.readInt(0, MOD - 1, "d");
        } else {
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            inf.readInt(l + 1, n, "r");
            inf.readSpace();
            inf.readInt(0, MOD - 1, "x");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
