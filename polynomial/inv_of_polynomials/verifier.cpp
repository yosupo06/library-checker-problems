#include <algorithm>
#include "testlib.h"
#include "random.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readChar(' ');
    int m = inf.readInt(1, N_MAX);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt((i == n-1) ? 1 : 0, MOD - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    for (int i = 0; i < m; i++) {
        inf.readInt((i == m-1) ? 1 : 0, MOD - 1);
        if (i != m - 1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
}
