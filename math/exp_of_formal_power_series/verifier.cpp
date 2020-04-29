#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(1, 500'000);
    inf.readChar('\n');

    inf.readInt(0, 0);    
    for (int i = 1; i < n; i++) {
        inf.readSpace();
        inf.readInt(0, 998244352);
    }    
    inf.readChar('\n');
    inf.readEof();
}
