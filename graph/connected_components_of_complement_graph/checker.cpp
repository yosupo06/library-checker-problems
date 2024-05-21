#include "testlib.h"
#include <algorithm>
#include <vector>

using namespace std;

vector<vector<int>> read_ans(int n, InStream &stream) {
    int k = stream.readInt(1, n);
    vector<vector<int>> cc(k);
    vector<int> pos(n, -1);
    for (int i = 0; i < k; i++) {
        int l = stream.readInt(1, n);
        cc[i] = vector<int>(l);
        for (int j = 0; j < l; j++) {
            cc[i][j] = stream.readInt(0, n - 1);
            if (pos[cc[i][j]] != -1) {
                stream.quitf(_wa, "twice used vertex %d", cc[i][j]);
            }
            pos[cc[i][j]] = i;
        }
        sort(cc[i].begin(), cc[i].end());
    }
    sort(cc.begin(), cc.end());
    return cc;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    auto cc_ans = read_ans(n, ans);
    auto cc_ouf = read_ans(n, ouf);
    int k_ans = int(cc_ans.size());
    int k_ouf = int(cc_ouf.size());
    if (k_ans != k_ouf) {
        quitf(_wa, "# of connected components is wrong - expected: '%d', found: '%d'", k_ans, k_ouf);
    }
    if (cc_ans != cc_ouf) {
        quitf(_wa, "connected components are different");
    }
    quitf(_ok, "OK");
}
