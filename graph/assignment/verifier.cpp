#include <iostream>

#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 500);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++){
            inf.readInt(-1'000'000'000, 1'000'000'000);
            if (j != n - 1) inf.readSpace();
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
