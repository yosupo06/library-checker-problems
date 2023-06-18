
#include "testlib.h"
#include "params.h"
using namespace std;

int main() {
    registerValidation();

    string s = inf.readToken();
    inf.readChar('\n');
    inf.readEof();
    int n = int(s.size());
    ensure(N_MIN <= n && n <= N_MAX);

    for (char c: s) {
        ensure(islower(c));
    }
    return 0;
}
