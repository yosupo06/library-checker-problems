#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    const size_t n = inf.readInt(0, N_MAX, "n");
    inf.readSpace();
    const size_t m = inf.readInt(0, M_MAX, "m");
    inf.readChar(LF);
    for (size_t i = 0; i < n; ++i) {
        inf.readLong(-U_MAX, U_MAX, "b"); // b
        inf.readChar(LF);
    }
    for (size_t i = 0; i < m; ++i) {
        inf.readInt(0, n - 1, "s");
        inf.readSpace();
        inf.readInt(0, n - 1, "t");
        inf.readSpace();
        const int64_t lower = inf.readLong(-U_MAX, U_MAX, "l");
        inf.readSpace();
        const int64_t upper = inf.readLong(-U_MAX, U_MAX, "u");
        ensure(lower <= upper);
        inf.readSpace();
        inf.readLong(-C_MAX, C_MAX, "c");
        inf.readChar(LF);
    }
    inf.readEof();
    return 0;
}
