#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    int t = inf.readInt(1, T_MAX, "T");
    inf.readChar('\n');
    for (int i = 0; i < t; ++i) {
        int n = inf.readInt(0, N_MAX, "N");
        inf.readSpace();
        inf.readInt(0, n, "K");
        inf.readChar('\n');
    }
    inf.readEof();
}
