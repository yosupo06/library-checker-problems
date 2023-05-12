#include "testlib.h"
#include "params.h"

void validate() {
    int n = inf.readInt(0, N_MAX);
    inf.readChar('\n');
    for (int i = 0; i < n; ++i) {
        inf.readInt(0, MOD - 1);
        if (i != n - 1) {
            inf.readSpace();
        }
    }
    inf.readChar('\n');
    for (int i = 0; i < n - 1; ++i) {
        inf.readInt(0, MOD - 1);
        if (i != n - 2) {
            inf.readSpace();
        }
    }
    inf.readChar('\n');
    inf.readEof();
}

int main() {
    registerValidation();
    validate();
}
