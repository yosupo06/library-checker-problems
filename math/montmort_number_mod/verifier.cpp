#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    inf.readLong(0LL, 1'000'000LL);
    inf.readSpace();
    inf.readLong(0LL, 1'000'000'000LL);
    inf.readEoln();
    inf.readEof();
}
