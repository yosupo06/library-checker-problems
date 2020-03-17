#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(0, N_MAX);
    inf.readChar('\n');
    for (int i = 0; i < (1 << n); i++) {
        inf.readInt(0, MOD - 1);
        if (i != (1 << n) - 1) inf.readSpace();
    }
    inf.readChar('\n');
    for (int i = 0; i < (1 << n); i++) {
        inf.readInt(0, MOD - 1);
        if (i != (1 << n) - 1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
