#include "testlib.h"
#include "params.h"
using namespace std;

int main() {
    registerValidation();

    int q = inf.readInt(Q_MIN, Q_MAX, "Q");
    inf.readChar('\n');

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 3, "t");
        if (t == 0 || t == 1) {
            inf.readSpace();
            char ch = inf.readChar();
            ensure('a' <= ch && ch <= 'z');
            length++;
        } else if (t == 2 || t == 3) {
            length--;
            ensure(length >= 0);
        }
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
