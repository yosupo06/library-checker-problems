#include "params.h"
#include "testlib.h"

int main() {
    registerValidation();

    int N = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    int Q = inf.readInt(Q_MIN, Q_MAX);
    inf.readChar('\n');

    for (int i = 0; i < N; i++) {
        int t = inf.readInt(0, 2);
        inf.readSpace();
        if (t == 0) {
            inf.readInt(X_MIN, X_MAX);
        } else {
            inf.readInt(-1, -1);
        }
        inf.readChar('\n');
    }

    for (int i = 0; i < Q; i++) {
        inf.readInt(0, N - 1);
        inf.readSpace();
        int a = inf.readInt(0, 2);
        inf.readSpace();
        if (a == 0) {
            inf.readInt(X_MIN, X_MAX);
        } else {
            inf.readInt(-1, -1);
        }
        inf.readChar('\n');
    }

    inf.readEof();
}
