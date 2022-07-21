#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX, "N");
    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(A_MIN, A_MAX, "a_i");
        if(i < n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
