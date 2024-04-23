#include "testlib.h"
#include "params.h"
#include <set>
#include <utility>
using namespace std;

int main() {
    registerValidation();
    int n = inf.readInt(N_MIN, N_MAX);
    inf.readSpace();
    int m = inf.readInt(M_MIN, M_MAX);
    inf.readChar('\n');
    set<pair<int, int>> edges;
    for (int i = 0; i < m; ++i) {
        int a = inf.readInt(0, n - 1);
        inf.readSpace();
        int b = inf.readInt(0, n - 1);
        inf.readChar('\n');
        ensure(a != b);
        if (a > b) {
            swap(a, b);
        }
        ensure(edges.count(make_pair(a, b)) == 0);
        edges.insert(make_pair(a, b));
    }
    inf.readEof();
}
