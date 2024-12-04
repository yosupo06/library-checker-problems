#include <iostream>
#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readChar('\n');

    for (int i = 1; i < n; i++) {
        inf.readInt(0, i - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');

    long long sum_c = 0;

    for (int i = 0; i < n; i++) {
        if (i != 0) inf.readSpace();
        int c = inf.readInt(C_MIN, C_MAX);
        sum_c += c;
    }
    inf.readChar('\n');
    ensure(sum_c <= C_SUM_MAX);

    long long sum_d = 0;

    for (int i = 0; i < n; i++) {
        if (i != 0) inf.readSpace();
        int d = inf.readInt(D_MIN, D_MAX);
        sum_d += d;
    }
    inf.readChar('\n');
    ensure(sum_d <= D_SUM_MAX);

    inf.readEof();
    return 0;
}
