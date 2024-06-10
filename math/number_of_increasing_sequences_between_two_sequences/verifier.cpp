#include "testlib.h"
#include "params.h"

#include <vector>
#include <cassert>

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, N_M_MAX); // a
    inf.readSpace();
    int m = inf.readInt(1, N_M_MAX); // b
    inf.readChar('\n');
    vector<int> a(n), b(n);
    for(int i = 0; i < n; i++){
        a[i] = inf.readInt(0, m);
        if(i < n - 1){
            inf.readSpace();
        }
    }
    inf.readChar('\n');
    for(int i = 0; i < n; i++){
        b[i] = inf.readInt(0, m);
        if(i < n - 1){
            inf.readSpace();
        }
    }
    inf.readChar('\n');
    for(int i = 0; i < n; i++){
        assert(a[i] < b[i]);
    }
    inf.readEof();
    return 0;
}