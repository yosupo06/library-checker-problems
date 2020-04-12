#include <algorithm>
#include <cassert>
#include "params.h"
#include "testlib.h"
using namespace std;


int main() {
    registerValidation();

    int n=inf.readInt(1, N_MAX);
    inf.readSpace();
    inf.readInt(1, M_MAX);

    inf.readChar('\n');

    for (int i = 0; i < n; i++) {
        inf.readInt(0, 998244353);
        if (i != n - 1) inf.readSpace();
    }
    inf.readChar('\n');
    inf.readEof();
}
