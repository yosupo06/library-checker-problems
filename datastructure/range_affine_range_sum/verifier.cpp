#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_AND_Q_MAX, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, MOD - 1, "a_i");        
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t == 0) {
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            inf.readInt(l + 1, n, "r");
            inf.readSpace();

            inf.readInt(1, MOD - 1, "b");
            inf.readSpace();
            inf.readInt(0, MOD - 1, "c");
        } else {
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            inf.readInt(l + 1, n, "r");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
