#include "testlib.h"
#include <string>

int main() {
    registerValidation();

    std::string s;
    s = inf.readToken();
    ensure(s == "p");
    inf.readSpace();
    s = inf.readToken();
    ensure(s == "cnf");
    inf.readSpace();    
    int n = inf.readInt(1, 500'000);
    inf.readSpace();
    int m = inf.readInt(1, 500'000);
    inf.readEoln();

    for (int i = 0; i < m; i++) {
        int a = inf.readInt(-n, n);
        ensure(a);
        inf.readSpace();
        int b = inf.readInt(-n, n);
        ensure(b);
        inf.readSpace();
        inf.readInt(0, 0);
        inf.readEoln();
    }
    
    inf.readEof();
    return 0;
}
