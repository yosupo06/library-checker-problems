#include <bits/stdc++.h>

#include "testlib.h"

int main() {
    registerValidation();
    int n = inf.readInt(1, 1 << 19);
    inf.readSpace();
    int m = inf.readInt(1, 1 << 19);
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        inf.readInt(0, 998244353 - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();
    for (int i = 0; i < m; i++) {
        inf.readInt(0, 998244353 - 1);
        if (i != m - 1) inf.readSpace();
    }
    inf.readEoln();

    inf.readEof();
    return 0;
}
