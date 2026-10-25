#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    int t = inf.readInt(1, T_MAX, "T");
    inf.readChar('\n');
    int total = 0;
    for (int i = 0; i < t; ++i) {
        int n = inf.readInt(1, N_SUM_MAX, "N");
        total += n;
        ensuref(total <= N_SUM_MAX, "Sum of lengths exceeds the limit");
        inf.readChar('\n');
        for (int j = 0; j < n; ++j) {
            if (j) inf.readSpace();
            inf.readUnsignedLong();
        }
        inf.readChar('\n');
    }
    inf.readEof();
}
