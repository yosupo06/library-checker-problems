#include <iostream>

#include "params.h"
#include "testlib.h"

int main() {
    registerValidation();
    int n = inf.readInt(0, N_MAX);
    inf.readChar('\n');
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; ++j) {
            inf.readInt(0, MOD - 1);
            if (j != n - 1) inf.readSpace();
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
