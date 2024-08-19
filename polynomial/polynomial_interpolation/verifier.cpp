#include <iostream>
#include <set>

#include "testlib.h"

int main() {
    registerValidation();
    int n = inf.readInt(1, 1 << 17);
    inf.readChar('\n');
    std::set<int> used;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt(0, 998244353 - 1);        
        if (i != n - 1) inf.readSpace();
        ensure(!used.count(x));
        used.insert(x);
    }
    inf.readChar('\n');
    for (int i = 0; i < n; i++) {
        inf.readInt(0, 998244353 - 1);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');

    inf.readEof();
    return 0;
}
