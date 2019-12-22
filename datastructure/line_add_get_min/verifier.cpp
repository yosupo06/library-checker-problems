#include "testlib.h"

const int MA = 1'000'000'000;
const long long MB = 1'000'000'000'000'000'000LL;

int main() {
    registerValidation();

    int n = inf.readInt(1, 200'000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200'000, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(-MA, MA, "a_i");
        inf.readSpace();
        inf.readLong(-MB, MB, "b_i");
        inf.readEoln();
    }
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t == 0) {
            inf.readInt(-MA, MA, "a");
            inf.readSpace();
            inf.readLong(-MB, MB, "b");
        } else {
            inf.readInt(-MA, MA, "p");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
