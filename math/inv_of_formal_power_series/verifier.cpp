#include <algorithm>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt((i == 0) ? 1 : 0, MOD - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
}
