#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 200000);
    inf.readSpace();
    int q = inf.readInt(1, 200000);
    inf.readChar('\n');

    for (int i = 0; i < q; i++) {
        inf.readInt(0, 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readChar('\n');
    }
    
    inf.readEof();
    return 0;
}
