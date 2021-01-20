#include <algorithm>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readSpace();
    inf.readLong(0, K_MAX);    
    inf.readChar('\n');
    
    for(int _ = 0; _ < 2; _++) {
        inf.readInt(0, MOD - 1);
        for (int i = 1; i < n; i++) {
            inf.readSpace();
            inf.readInt(0, MOD - 1);
        }
        inf.readChar('\n');
    }
    inf.readEof();
}
