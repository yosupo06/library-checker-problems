#include "testlib.h"
#include "params.h"

using ll = long long;

int main() {
    registerValidation();

    int n = inf.readInt(N_AND_Q_MIN, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(N_AND_Q_MIN, N_AND_Q_MAX, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        int l = inf.readInt(-A_ABS_MAX, A_ABS_MAX, "l_i");
        inf.readSpace();
        int r = inf.readInt(-A_ABS_MAX, A_ABS_MAX, "r_i");
        ensure(l < r);
        inf.readSpace();
        inf.readInt(-A_ABS_MAX, A_ABS_MAX, "a_i");
        inf.readSpace();
        inf.readLong(-B_ABS_MAX, B_ABS_MAX, "b_i");
        inf.readEoln();
    }
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");
        inf.readSpace();
        if (t == 0) {
            int l = inf.readInt(-A_ABS_MAX, A_ABS_MAX, "l");
            inf.readSpace();
            int r = inf.readInt(-A_ABS_MAX, A_ABS_MAX, "r");
            ensure(l < r);
            inf.readSpace();
            inf.readInt(-A_ABS_MAX, A_ABS_MAX, "a");
            inf.readSpace();
            inf.readLong(-B_ABS_MAX, B_ABS_MAX, "b");
        } else {
            inf.readInt(-A_ABS_MAX, A_ABS_MAX, "p");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
