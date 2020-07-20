#include <iostream>
#include <set>
#include <utility>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(A_MIN, A_MAX);
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readChar('\n');
        }
    }

    inf.readEof();
    return 0;
}
