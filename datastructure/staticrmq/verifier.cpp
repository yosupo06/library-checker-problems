#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000);
    inf.readSpace();
    int q = inf.readInt(1, 500'000);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1'000'000'000);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    for (int i = 0; i < q; i++) {
        int a = inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(a + 1, n);
        inf.readChar('\n');
    }    
    inf.readEof();
    return 0;
}
