#include <algorithm>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, int(N_MAX));
    inf.readChar('\n');

    inf.readInt(0, 0);    
    for (int i = 1; i < n; i++) {
        inf.readSpace();
        inf.readInt(0, int(MOD - 1));
    }    
    inf.readChar('\n');
    inf.readEof();
}
