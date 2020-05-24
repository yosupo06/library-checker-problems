#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int Q = inf.readInt(1, Q_MAX);
    inf.readChar('\n');

    for (int i = 0; i < Q; i++) {
        int t = inf.readInt(0, 1);
        if (t == 0) {
            inf.readSpace();
            inf.readLong(0, K_AND_V_MAX, "k");
            inf.readSpace();
            inf.readLong(0, K_AND_V_MAX, "v");            
        } else {
            inf.readSpace();
            inf.readLong(0, K_AND_V_MAX, "k");
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
