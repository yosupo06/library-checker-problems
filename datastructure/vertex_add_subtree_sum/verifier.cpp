#include "testlib.h"
#include <vector>

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000, "N");
    inf.readSpace();
    int q = inf.readInt(1, 500'000, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1'000'000'000, "a_i");
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();

    for (int i = 1; i < n; i++) {
        inf.readInt(0, i - 1, "p_i");
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();

    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");        
        inf.readSpace();
        if (t == 0) {
            inf.readInt(0, n - 1, "u");
            inf.readSpace();
            inf.readInt(0, 1'000'000'000, "x");
        } else {
            inf.readInt(0, n - 1, "u");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
