#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    const int n = inf.readInt(2, N_MAX, "N");
    inf.readSpace();
    const int m = inf.readInt(0, M_MAX, "M");
    inf.readSpace();
    const int s = inf.readInt(0, n - 1, "S");
    inf.readSpace();
    const int t = inf.readInt(0, n - 1, "T");
    ensure(s != t);
    inf.readChar('\n');
    for (int i = 0; i < m; ++i) {
        inf.readInt(0, n - 1, "u");
        inf.readSpace();
        inf.readInt(0, n - 1, "v");
        inf.readSpace();
        inf.readLong(0, C_MAX, "c");
        inf.readChar('\n');
    }
    inf.readEof();
}
