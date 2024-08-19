#include <algorithm>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(2, int(N_MAX));
    inf.readChar('\n');

    inf.readInt(0, 0);    
    for (int i = 1; i < n; i++) {
        inf.readSpace();
        int a_i=inf.readInt(0, int(MOD - 1));
        if(i==1){
            ensure(a_i!=0);
        }
    }    
    inf.readChar('\n');
    inf.readEof();
}
