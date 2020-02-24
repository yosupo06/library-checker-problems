#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readEoln();
    for (int i = 0; i < n; i++) {
        inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readSpace();
        inf.readInt(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        inf.readEoln();
    }
    inf.readEof();
    return 0;
}
