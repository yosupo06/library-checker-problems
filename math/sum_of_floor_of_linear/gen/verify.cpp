#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();
    int t = inf.readInt(1, 100'000);
    inf.readEoln();
    for (int i = 0; i < t; i++) {
        int n = inf.readInt(1, 1'000'000'000);
        inf.readSpace();
        int m = inf.readInt(1, 1'000'000'000);
        inf.readSpace();
        int a = inf.readInt(0, m - 1);
        inf.readSpace();
        int b = inf.readInt(0, m - 1);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
