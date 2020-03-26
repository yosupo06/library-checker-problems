#include <algorithm>
#include <cassert>
#include "params.h"
#include "testlib.h"
using namespace std;


int main() {
    registerValidation();
    long long N = inf.readLong(1, N_MAX);
    N++;N--;
    inf.readChar('\n');
    inf.readEof();
}
