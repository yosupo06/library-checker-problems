#include "testlib.h"
#include "params.h"
#include <set>
#include <utility>

int main() {
    registerValidation();

    int n = inf.readInt(2, N_MAX);
    inf.readChar('\n');

    std::set<std::pair<int, int>> points;

    for (int i = 0; i < n; i++) {
        int x = inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readSpace();
        int y = inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readChar('\n');

        bool inserted = points.insert({x, y}).second;
        ensuref(inserted, "duplicate point at index %d: (%d, %d)", i, x, y);
    }
    inf.readEof();
    return 0;
}
