#include "testlib.h"

int main(int argc, char** argv) {
    // Ten million uint64 values require up to about 210 MB of text.
    inf.maxFileSize = ans.maxFileSize = ouf.maxFileSize = 256 * 1024 * 1024;
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
