#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_AND_Q_MAX, "Q");
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(0, A_AND_X_MAX, "a_i");
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t == 0) {
            inf.readInt(0, n - 1, "p");
            inf.readSpace();
            inf.readInt(0, A_AND_X_MAX, "x");
        } else {
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            inf.readInt(l + 1, n, "r");
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
