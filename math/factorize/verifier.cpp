#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();
    int q = inf.readInt(1, 100);
    inf.readChar('\n');
    for (int i = 0; i < q; i++) {
        inf.readLong(1, 1'000'000'000'000'000'000LL);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
