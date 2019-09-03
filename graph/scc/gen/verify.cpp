#include <bits/stdc++.h>

#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000);
    inf.readSpace();
    int m = inf.readInt(1, 500'000);
    inf.readEoln();

    for (int i = 1; i < m; i++) {
        inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
