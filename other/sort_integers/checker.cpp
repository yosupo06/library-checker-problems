#include "testlib.h"

int main(int argc, char** argv) {
    registerTestlibCmd(argc, argv);
    int position = 0;
    while (!ans.seekEof()) {
        auto expected = ans.readUnsignedLong();
        auto actual = ouf.readUnsignedLong();
        if (actual != expected) quitf(_wa, "Output position %d differs", position);
        ++position;
    }
    if (!ouf.seekEof()) quitf(_wa, "Extra output");
    quitf(_ok, "%d values", position);
}
