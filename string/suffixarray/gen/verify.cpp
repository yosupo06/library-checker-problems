#include <bits/stdc++.h>

#include "testlib.h"
using namespace std;

int main() {
    registerValidation();

    string s = inf.readToken();
    inf.readEoln();
    inf.readEof();
    int n = int(s.size());
    ensure(1 <= n && n <= 500'000);

    for (char c: s) {
        ensure(islower(c));
    }
    return 0;
}
