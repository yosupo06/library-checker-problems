#include <set>
#include <utility>
#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    int left = inf.readInt(1, L_MAX);
    inf.readSpace();
    int right = inf.readInt(1, R_MAX);
    inf.readSpace();
    int m = inf.readInt(1, M_MAX);
    inf.readChar('\n');
    std::set<std::pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, left - 1);
        inf.readSpace();
        int b = inf.readInt(0, right - 1);
        inf.readChar('\n');
        ensuref(edges.emplace(a, b).second, "duplicate edge (%d, %d)", a, b);
    }
    inf.readEof();
}
