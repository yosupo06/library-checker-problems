#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000);
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt((i == 0) ? 1 : 0, 998244353);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
}
