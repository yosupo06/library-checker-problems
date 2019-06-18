#include <bits/stdc++.h>

#include "testlib.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, 3000);
    inf.readSpace();
    int k = inf.readInt(1, 10000);
    inf.readEoln();
    std::set<std::pair<int, int>> st;
    for (int i = 0; i < k; i++) {
        int a = inf.readInt(0, n - 1);
        inf.readSpace();
        int b = inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, 998244353 - 1);
        inf.readEoln();
        ensure(!st.count({a, b}));
        st.insert({a, b});
    }
    inf.readEof();
    return 0;
}
