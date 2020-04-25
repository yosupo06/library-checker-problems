#include "testlib.h"
#include "params.h"
#include <vector>

int main() {
    registerValidation();

    int N = inf.readInt(1, MAX_N);
    inf.readSpace();
    int Q = inf.readInt(1, MAX_Q);
    inf.readChar('\n');

    std::vector<int> tp(Q);
    for(int i=0; i<Q; i++) {
        int t = inf.readInt(0, 1);
        inf.readSpace();
        int k = inf.readInt(-1, i-1);
        inf.readSpace();
        inf.readInt(0, N-1); // u
        inf.readSpace();
        inf.readInt(0, N-1); // v
        inf.readEoln();
        ensuref(k == -1 or tp[k] == 0, "the value of k is invalid");
        tp[i] = t;
    }
    
    inf.readEof();
    return 0;
}
