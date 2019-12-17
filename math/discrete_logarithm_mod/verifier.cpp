#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int t = inf.readInt(1, 100);
    inf.readEoln();

    for (int i = 0; i < t; i++) {
        int x = inf.readInt(0, 1'000'000'000);
        inf.readSpace();
        int y = inf.readInt(0, 1'000'000'000);
        inf.readSpace();
        int m = inf.readInt(1, 1'000'000'000);
        inf.readEoln();
        ensure(x < m);
        ensure(y < m);
    }
    inf.readEof();
}
