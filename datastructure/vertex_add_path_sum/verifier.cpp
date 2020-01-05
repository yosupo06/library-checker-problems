#include "testlib.h"
#include "params.h"
#include <vector>

struct UnionFind {
    std::vector<int> p, r;
    int gn;
    UnionFind(int n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) { return group(a) == group(b); }
};

int main() {
    registerValidation();

    int n = inf.readInt(1, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_AND_Q_MAX, "Q");
    inf.readEoln();

    for (int i = 0; i < n; i++) {
        inf.readInt(0, A_AND_X_MAX, "a_i");
        if (i != n - 1) inf.readSpace();
    }
    inf.readEoln();

    auto uf = UnionFind(n);
    for (int i = 0; i < n - 1; i++) {
        int a = inf.readInt(0, n - 1, "u_i");
        inf.readSpace();
        int b = inf.readInt(0, n - 1, "v_i");
        inf.readEoln();
        ensure(!uf.same(a, b));
        uf.merge(a, b);
    }

    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 1, "t");        
        inf.readSpace();
        if (t == 0) {
            inf.readInt(0, n - 1, "p");
            inf.readSpace();
            inf.readInt(0, A_AND_X_MAX, "x");
        } else {
            inf.readInt(0, n - 1, "u");
            inf.readSpace();
            inf.readInt(0, n - 1, "v");
        }
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
