#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 200'000);
    inf.readSpace();
    int q = inf.readInt(1, 200'000);
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1'000'000'000);
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();
    for (int i = 0; i < q; i++) {
        int l = inf.readInt(0, n - 1);
        inf.readSpace();
        int r = inf.readInt(l + 1, n);
        inf.readSpace();
        inf.readInt(0, r - l - 1);
        inf.readEoln();
    }    
    inf.readEof();
    return 0;
}
