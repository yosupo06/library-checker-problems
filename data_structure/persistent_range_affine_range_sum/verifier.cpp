#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(0, MOD - 1, "a_i");        
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    
    // index +1
    std::vector<int> has_data(q + 1, 0);
    has_data[0] = 1;

    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 2, "t");
        inf.readSpace();
        int k = inf.readInt(-1, i - 1, "k");
        inf.readSpace();
        ensuref(has_data[k + 1] == 1, "the value of k is invalid");
        if (t == 0) {
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n, "r");
            inf.readSpace();
            inf.readInt(1, MOD - 1, "b");
            inf.readSpace();
            inf.readInt(0, MOD - 1, "c");
            ensure(l < r);
            has_data[i + 1] = 1;
        } else if(t == 1) {
            int s = inf.readInt(-1, i - 1, "s");
            inf.readSpace();
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n, "r");
            ensure(l < r);
            ensuref(has_data[s + 1] == 1, "the value of s is invalid");
            has_data[i + 1] = 1;
        } else if(t == 2) {
            int l = inf.readInt(0, n - 1, "l");
            inf.readSpace();
            int r = inf.readInt(0, n, "r");
            ensure(l < r);
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
