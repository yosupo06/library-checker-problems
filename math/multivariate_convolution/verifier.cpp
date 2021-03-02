#include <iostream>

#include "params.h"
#include "testlib.h"

int main() {
    registerValidation();
    int k = inf.readInt(0, K_MAX);
    inf.readChar('\n');
    int N = 1;
    for (int i = 0; i < k; i++) {
        int n = inf.readInt(1, PROD_N_MAX);
        ensure(1LL * N * n <= PROD_N_MAX);
        N *= n;

        if (i + 1 < k) inf.readChar(' ');
    }
    inf.readChar('\n');

    for (int i = 0; i < N; i++) {
        inf.readInt(0, MOD - 1);
        if (i + 1 < N) inf.readChar(' ');
    }
    inf.readChar('\n');
    for (int i = 0; i < N; i++) {
        inf.readInt(0, MOD - 1);
        if (i + 1 < N) inf.readChar(' ');
    }
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
