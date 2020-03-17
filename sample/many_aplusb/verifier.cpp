#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int t = inf.readInt(1, T_MAX);
    inf.readChar('\n');
    for (int i = 0; i < t; i++) {
        inf.readLong(0, A_AND_B_MAX);  // a
        inf.readSpace();
        inf.readLong(0, A_AND_B_MAX);  // b
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
