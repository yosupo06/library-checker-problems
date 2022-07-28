#include <iostream>
#include <tuple>
#include <set>

#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX, "n");
    inf.readSpace();
    int m = inf.readInt(0, n * (n - 1) / 2, "m");
    inf.readChar('\n');

    using P = std::pair<int, int>;
    std::set<P> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt(0, n - 1, "u_i");
        inf.readSpace();
        int v = inf.readInt(0, n - 1, "v_i");
        inf.readSpace();
        inf.readInt(W_MIN, W_MAX, "w_i");
        inf.readChar('\n');
        ensuref(u != v, "u != v");
        if (u > v) {
            std::swap(u, v);
        }
        ensuref(edges.find({u, v}) == edges.cend(), "duplicate edge");
        edges.insert({u, v});
    }
    inf.readEof();
    return 0;
}
