#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    int q = inf.readInt(Q_MIN, Q_MAX);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(A_MIN, A_MAX);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    for (int i = 0; i < q; i++) {
        int l = inf.readInt(0, n - 1);
        inf.readSpace();
        int r = inf.readInt(l + 1, n);
        inf.readSpace();
        inf.readInt(0, r - l - 1);
        inf.readChar('\n');
    }    
    inf.readEof();
    return 0;
}
