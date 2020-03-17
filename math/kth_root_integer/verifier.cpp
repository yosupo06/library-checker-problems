#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int t = inf.readInt(1, 500'000);
    inf.readChar('\n');

    for (int i = 0; i < t; i++) {        
        inf.readUnsignedLong();
        inf.readSpace();
        inf.readInt(1, 64);
        inf.readChar('\n');
    }
    inf.readEof();
}
