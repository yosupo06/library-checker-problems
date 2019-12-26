#include "testlib.h"

constexpr int MOD = 998244353;
int main() {
    registerValidation();

    int q = inf.readInt(1, 500'000, "Q");
    inf.readEoln();

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 2, "t");
        if (t == 0) {
            inf.readSpace();
            inf.readInt(1, MOD - 1, "a");
            inf.readSpace();
            inf.readInt(0, MOD - 1, "b");
            length++;
        } else if (t == 1) {
            length--;
            ensure(length >= 0);
        } else {
            inf.readSpace();
            inf.readInt(0, MOD - 1, "x");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
