#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    int m = inf.readInt(M_MIN, M_MAX);
    inf.readChar('\n');

    for (int i = 0; i != m; i += 1) {
        int u = inf.readInt(0, n - 1);
        inf.readSpace();
        int v = inf.readInt(0, n - 1);
        ensure(u != v);
        inf.readChar('\n');
    }

    inf.readEof();
}
