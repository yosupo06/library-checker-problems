#include <iostream>
#include <unordered_set>
#include <utility>
#include "testlib.h"
#include "params.h"

using namespace std;

int main() {
    registerValidation();

    int n = inf.readInt(N_MIN, N_MAX, "N");
    inf.readChar('\n');

    unordered_set<int> used;
    for (int i = 0; i < n; i++) {
        int a_i = inf.readInt(A_MIN, A_MAX, "a_i");
        ensuref(not used.count(a_i), "the sequence A should be distinct.");
        used.insert(a_i);
        if (i + 1 < n) {
            inf.readSpace();
        } else {
            inf.readChar('\n');
        }
    }

    inf.readEof();
    return 0;
}
