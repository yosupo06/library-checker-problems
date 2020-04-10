#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    int N = inf.readInt(1, MAX_N);
    inf.readSpace();
    int Q = inf.readInt(1, MAX_Q);
    inf.readChar('\n');

    for(int i=0; i<N; i++) {
        inf.readInt(0, MAX_A);
        if(i + 1 == N) inf.readChar('\n');
        else inf.readSpace();
    }

    for(int i=0; i<Q; i++) {
        int l = inf.readInt(0, N-1);
        inf.readSpace();
        inf.readInt(l+1, N);
        inf.readChar('\n');
    }
    
    inf.readEof();
    return 0;
}
