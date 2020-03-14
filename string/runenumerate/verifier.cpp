#include <iostream>

#include "testlib.h"
using namespace std;

int main() {
    registerValidation();

    string s = inf.readToken();
    inf.readChar('\n');
    inf.readEof();
    int n = int(s.size());
    ensure(1 <= n && n <= 200'000);

    for (char c: s) {
        ensure(islower(c));
    }
    return 0;
}
