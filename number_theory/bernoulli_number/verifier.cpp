#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();
    inf.readInt(0, 500'000);
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
