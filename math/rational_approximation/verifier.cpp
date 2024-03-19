#include <iostream>
#include "params.h"
#include "testlib.h"

int main() {
    registerValidation();
    int t = inf.readInt(1, MAX_T);
    inf.readChar('\n');
    for (int i = 0; i < t; i++) {
        inf.readLong(1, MAX_N);
        inf.readChar(' ');
        inf.readLong(1, MAX_N);
        inf.readChar(' ');
        inf.readLong(1, MAX_N);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
