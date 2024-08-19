#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();
    inf.readLong(N_MIN, N_MAX, "N");
    inf.readChar('\n');
    inf.readEof();
    return 0;
}
