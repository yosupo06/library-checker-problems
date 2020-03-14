#include <iostream>
#include "params.h"

#include "testlib.h"
int main() {
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readSpace();
    int k = inf.readInt(1, M_MAX);
    inf.readChar('\n');
    std::set<std::pair<int, int>> st;
    for (int i = 0; i < k; i++) {
        int a = inf.readInt(0, n - 1);
        inf.readSpace();
        int b = inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(1, MOD - 1);
        inf.readChar('\n');
        ensure(!st.count({a, b}));
        st.insert({a, b});
    }
    inf.readEof();
    return 0;
}
