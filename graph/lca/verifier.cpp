#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(2, 500'000);
    inf.readSpace();
    int q = inf.readInt(1, 500'000);
    inf.readChar('\n');

    for (int i = 1; i < n; i++) {
        inf.readInt(0, i - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');

    for (int i = 0; i < q; i++) {
        int u = inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(u + 1, n - 1);
        inf.readChar('\n');
    }

    inf.readEof();
    return 0;
}
