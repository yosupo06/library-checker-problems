#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readChar('\n');
    for (int i = 0; i < n; i++) {
        inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readChar(' ');
        inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readChar('\n');
    }
    int m = inf.readInt(1, M_MAX);
    inf.readChar('\n');
    for (int i = 0; i < m; i++) {
        inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readChar(' ');
        inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readChar('\n');
    }
    int q = inf.readInt(1, Q_MAX);
    inf.readChar('\n');
    for (int i = 0; i < q; i++) {
        inf.readInt(0, n-1);
        inf.readChar(' ');
        inf.readInt(0, n-1);
        inf.readChar(' ');
        inf.readInt(0, n-1);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
