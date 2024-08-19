#include "testlib.h"
#include "params.h"

#include <vector>

int main() {
    registerValidation();

    const int q = inf.readInt(Q_MIN, Q_MAX);
    inf.readChar('\n');

    std::vector<int> size_(q + 1);
    const auto size = size_.begin() + 1;
    size[-1] = 0;

    for (int i = 0; i != q; i += 1) {
        int c = inf.readInt(0, 1);
        inf.readSpace();
        switch (c) {
            case 0: {
                const int t = inf.readInt(-1, i - 1);
                inf.readSpace();
                inf.readInt(X_MIN, X_MAX);
                size[i] = size[t] + 1;
            } break;
            case 1: {
                const int t = inf.readInt(-1, i - 1);
                ensuref(size[t] != 0, "S_t must not be empty");
                size[i] = size[t] - 1;
            } break;
        }
        inf.readChar('\n');
    }

    inf.readEof();
}
