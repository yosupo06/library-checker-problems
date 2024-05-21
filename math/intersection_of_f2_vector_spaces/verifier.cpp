#include <vector>

#include "testlib.h"
#include "params.h"
#include "binary_mat.h"

bool is_indep(const std::vector<int> &x) {
    BinaryMat mat;
    for (int v: x) {
        if (!mat.is_indep(v)) return false;
        mat.add(v);
    }
    return true;
}

int main() {
    registerValidation();

    int T = inf.readInt(1, T_MAX);
    inf.readChar('\n');

    for (int t = 0; t < T; ++t) {
        int n = inf.readInt(0, NM_MAX);
        std::vector<int> u(n);
        for (int i = 0; i < n; i++) {
            inf.readSpace();
            u[i] = inf.readInt(0, UV_MAX);
        }
        inf.readChar('\n');
        int m = inf.readInt(0, NM_MAX);
        std::vector<int> v(m);
        for (int i = 0; i < m; i++) {
            inf.readSpace();
            v[i] = inf.readInt(0, UV_MAX);
        }
        inf.readChar('\n');
        if (!is_indep(u)) {
            quitf(_wa, "u is not linearly independent");
        }
        if (!is_indep(v)) {
            quitf(_wa, "v is not linearly independent");
        }
    }
    inf.readEof();

    return 0;
}
