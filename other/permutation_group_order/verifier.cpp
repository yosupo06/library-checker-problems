#include <vector>
#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    int n = inf.readInt(1, N_MAX, "N");
    inf.readSpace();
    int k = inf.readInt(1, K_MAX, "K");
    inf.readChar('\n');
    for (int i = 0; i < k; ++i) {
        std::vector<bool> seen(n);
        for (int j = 0; j < n; ++j) {
            if (j) inf.readSpace();
            int x = inf.readInt(0, n - 1, "P_i_j");
            ensuref(!seen[x], "Each row must be a permutation");
            seen[x] = true;
        }
        inf.readChar('\n');
    }
    inf.readEof();
}
