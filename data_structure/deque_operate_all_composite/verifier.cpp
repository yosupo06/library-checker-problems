#include "testlib.h"

constexpr int MOD = 998244353;
int main() {
    registerValidation();

    int q = inf.readInt(1, 500'000, "Q");
    inf.readChar('\n');

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 4, "t");
        if (t == 0 || t == 1) {
            inf.readSpace();
            inf.readInt(1, MOD - 1, "a");
            inf.readSpace();
            inf.readInt(0, MOD - 1, "b");
            length++;
        } else if (t == 2 || t == 3) {
            length--;
            ensure(length >= 0);
        } else {
            inf.readSpace();
            inf.readInt(0, MOD - 1, "x");
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
