#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int t = inf.readInt(1, 1000);
    inf.readChar('\n');

    set<long long> trusted;
    for (int i = 0; i < t; i++) {
        inf.readLong(0LL, 1'000'000'000LL);
        inf.readSpace();
        inf.readLong(0LL, 1'000'000'000LL);
        inf.readSpace();
        inf.readLong(1LL, 1'000'000'000LL);
        inf.readChar('\n');
    }
    inf.readEof();
}
