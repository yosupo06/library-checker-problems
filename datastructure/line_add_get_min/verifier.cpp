#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_AND_Q_MIN, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(N_AND_Q_MIN, N_AND_Q_MAX, "Q");
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(-A_ABS_MAX, A_ABS_MAX, "a_i");
        inf.readSpace();
        inf.readLong(-B_ABS_MAX, B_ABS_MAX, "b_i");
        inf.readChar('\n');
    }
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t == 0) {
            inf.readInt(-A_ABS_MAX, A_ABS_MAX, "a");
            inf.readSpace();
            inf.readLong(-B_ABS_MAX, B_ABS_MAX, "b");
        } else {
            inf.readInt(-A_ABS_MAX, A_ABS_MAX, "p");
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
