#include <algorithm>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, NM_MAX);
    inf.readSpace();
    int m = inf.readInt(1, NM_MAX);
    inf.readChar('\n');
    ensuref(1L * n * m <= NM_MAX, "n*m must be <= NM_MAX");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; ++j) {
            inf.readInt((i == 0 && j == 0) ? 1 : 0, MOD - 1);
            if (j != m - 1) inf.readSpace();
        }
        inf.readChar('\n');
    }
    inf.readEof();
}
