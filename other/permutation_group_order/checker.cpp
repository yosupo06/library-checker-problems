#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int expected = ans.readInt();
    int actual = ouf.readInt(0, 998244352);
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    if (expected != actual) quitf(_wa, "Expected %d, found %d", expected, actual);
    quitf(_ok, "%d", actual);
}
