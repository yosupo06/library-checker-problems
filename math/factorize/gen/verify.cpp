#include <bits/stdc++.h>

#include "testlib.h"

int main() {
    registerValidation();
    int q = inf.readInt(1, 100);
    inf.readEoln();
    for (int i = 0; i < q; i++) {
        inf.readLong(1, 1'000'000'000'000'000'000LL);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
