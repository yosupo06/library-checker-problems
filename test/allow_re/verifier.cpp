#include "testlib.h"

int main() {
    registerValidation();

    inf.readInt(0, 1'000'000'000); // a
    inf.readSpace();
    inf.readInt(0, 1'000'000'000); // b
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
