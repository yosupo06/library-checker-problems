#include <algorithm>
#include "testlib.h"

using namespace std;

int main() {
    registerValidation();

    int t = inf.readInt(1, 10'000);
    inf.readEoln();

    set<long long> trusted;
    for (int i = 0; i < t; i++) {
        inf.readLong(0LL, 1'000'000'000LL);
        inf.readSpace();
        inf.readLong(0LL, 1'000'000'000LL);
        inf.readSpace();
        inf.readLong(1LL, 1'000'000'000LL);
        inf.readEoln();
    }
    inf.readEof();
}
