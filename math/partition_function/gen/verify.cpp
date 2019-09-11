#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();
    inf.readInt(0, 500'000);
    inf.readEoln();
    inf.readEof();
    return 0;
}
