#include <map>
#include <utility>
#include <vector>
#include <algorithm>

#include "testlib.h"

using namespace std;
using ll = long long;

struct P {
    ll x, y;
    int pos() const {
        if (y < 0) return -1;
        if (y == 0 && 0 <= x) return 0;
        return 1;
    }
    bool operator<(P r) const {
        if (pos() != r.pos()) return pos() < r.pos();
        return 0 < (x * r.y - y * r.x);
    }
};

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);

    // input
    int n = inf.readInt();
    multiset<pair<int, int>> input_set;
    for (int i = 0; i < n; i++) {
        int x = inf.readInt();
        int y = inf.readInt();
        input_set.insert({x, y});
    }

    multiset<pair<int, int>> actual_set;
    vector<P> actual(n);
    for (int i = 0; i < n; i++) {
        int x = ouf.readInt();
        int y = ouf.readInt();
        actual_set.insert({x, y});
        actual[i] = {x, y};
    }

    if (input_set != actual_set) {
        quitf(_wa, "Do not use each point exactly once");
    }

    for (int i = 0; i < n - 1; i++) {
        if (actual[i + 1] < actual[i]) {
            quitf(_wa, "Order is not correct");
        }
    }

    quitf(_ok, "OK");
}
