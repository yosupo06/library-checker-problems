#include <iostream>
#include <algorithm>
#include "testlib.h"
#include "params.h" 

using namespace std;

int main() {
    registerValidation();

    int N = inf.readInt(1, N_MAX);
    inf.readSpace();
    int T = inf.readInt(1, T_MAX);
    inf.readChar('\n');
    for (int i = 0; i < N; i++) {
        inf.readInt(1, T);
        if(i != N-1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
    return 0;
}