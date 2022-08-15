#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();
    int t = inf.readInt(1, 100'000);
    inf.readChar('\n');
    for (int i = 0; i < t; i++) {
        inf.readInt(1, 1'000'000'000);
        inf.readSpace();
        int m = inf.readInt(1, 1'000'000'000);
        inf.readSpace();
        inf.readInt(0, m - 1);
        inf.readSpace();
        inf.readInt(0, m - 1);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
