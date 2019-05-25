#include <bits/stdc++.h>

#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 200000);
    inf.readSpace();
    int q = inf.readInt(1, 200000);
    inf.readEoln();

    for (int i = 0; i < q; i++) {
        inf.readInt(0, 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, n - 1);
        inf.readEoln();
    }
    
    inf.readEof();
    return 0;
}
