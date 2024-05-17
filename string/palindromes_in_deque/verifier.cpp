#include "testlib.h"
#include "params.h"
using namespace std;

int main() {
    registerValidation();

    int q = inf.readInt(1, Q_MAX, "Q");
    inf.readChar('\n');

    int length = 0;
    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 3, "t");
        if (t == 0 || t == 1) {
            inf.readSpace();
            inf.readChar();
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
