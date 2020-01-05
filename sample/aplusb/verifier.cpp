#include "testlib.h"
#include "params.h"

int main() {
    registerValidation();

    inf.readInt(0, A_AND_B_MAX); // a
    inf.readSpace();
    inf.readInt(0, A_AND_B_MAX); // b
    inf.readEoln();
    inf.readEof();
    return 0;
}
