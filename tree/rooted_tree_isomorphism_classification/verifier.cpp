#include <iostream>
#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readChar('\n');

    for (int i = 1; i < n; i++) {
        inf.readInt(0, i - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');

    inf.readEof();
    return 0;
}
