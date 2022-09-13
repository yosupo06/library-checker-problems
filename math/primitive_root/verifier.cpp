#include <iostream>
#include "params.h"
#include "testlib.h"

int main() {
    registerValidation();
    int q = inf.readInt(1, MAX_Q);
    inf.readChar('\n');
    for (int i = 0; i < q; i++) {
        inf.readLong(1, MAX_A);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
