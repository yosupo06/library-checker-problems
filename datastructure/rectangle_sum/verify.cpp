#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 200'000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 200'000, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1'000'000'000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1'000'000'000, "y_i");
        inf.readSpace();
        inf.readInt(0, 1'000'000'000, "w_i");
        inf.readEoln();
    }
    for (int i = 0; i < q; i++) {
        int l = inf.readInt(0, 1'000'000'000, "l_i");
        inf.readSpace();
        int d = inf.readInt(0, 1'000'000'000, "d_i");
        inf.readSpace();
        inf.readInt(l + 1, 1'000'000'000, "r_i");
        inf.readSpace();
        inf.readInt(d + 1, 1'000'000'000, "u_i");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
