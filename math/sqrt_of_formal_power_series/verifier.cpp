#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000);
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 998244353);
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();
    inf.readEof();
}
