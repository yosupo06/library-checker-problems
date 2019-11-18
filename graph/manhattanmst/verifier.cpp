#include <iostream>
#include <set>
#include <utility>
#include "testlib.h"
#include <queue>

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, 200'000, "n");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 1'000'000'000, "x_i");
        inf.readSpace();
        inf.readInt(0, 1'000'000'000, "y_i");
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
