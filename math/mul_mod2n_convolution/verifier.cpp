#include <iostream>

#include "params.h"
#include "testlib.h"

int main(){
    registerValidation();
    int n = inf.readInt(0, N_MAX);
    inf.readChar('\n');
    const int N = 1 << n;

    inf.readInts(N, 0, MOD - 1);
    inf.readChar('\n');
    
    inf.readInts(N, 0, MOD - 1);
    inf.readChar('\n');

    inf.readEof();
    return 0;
}
