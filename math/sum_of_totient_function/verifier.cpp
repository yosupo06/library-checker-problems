#include <algorithm>
#include <cassert>
#include "params.h"
#include "testlib.h"
using namespace std;


int main() {
    registerValidation();
    inf.readLong(1, N_MAX);
    inf.readChar('\n');
    inf.readEof();
}
