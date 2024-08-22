#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int N = inf.readInt(1, N_MAX);
    inf.readChar('\n');

    for (int i = 0; i < N; i++) {
        int L=inf.readInt(0,COORD_MAX);
        inf.readSpace();
        int D=inf.readInt(0,COORD_MAX);
        inf.readSpace();
        int R=inf.readInt(0,COORD_MAX);
        inf.readSpace();
        int U=inf.readInt(0,COORD_MAX);
        inf.readChar('\n');
        ensure(L<R);
        ensure(D<U);
    }
    inf.readEof();
    return 0;
}
