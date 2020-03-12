#include <algorithm>
#include <vector>
#include "testlib.h"

using namespace std;

// check and return bc
vector<vector<int>> read_ans(int m, InStream& stream) {
    int k = stream.readInt(1, m);
    vector<vector<int>> bcs(k);
    vector<int> pos(m, -1);
    for (int i = 0; i < k; i++) {
        int l = stream.readInt(1, m);
        bcs[i] = vector<int>(l);
        for (int j = 0; j < l; j++) {
            bcs[i][j] = stream.readInt(0, m - 1);
            if (pos[bcs[i][j]] != -1) {
                stream.quitf(_wa, "twice used edge %d", bcs[i][j]);
            }
            pos[bcs[i][j]] = i;
        }
        sort(bcs[i].begin(), bcs[i].end());
    }
    return bcs;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    inf.readInt(); inf.readSpace();
    int m = inf.readInt();

    auto bcs_ans = read_ans(m, ans);
    auto bcs_ouf = read_ans(m, ouf);
    int k_ans = int(bcs_ans.size());
    int k_ouf = int(bcs_ouf.size());
    if (k_ans != k_ouf) {
        quitf(_wa, "# of bc is differ - expected: '%d', found: '%d'", k_ans, k_ouf);
    }

    sort(bcs_ans.begin(), bcs_ans.end());
    sort(bcs_ouf.begin(), bcs_ouf.end());

    if (bcs_ans != bcs_ouf) {
        quitf(_wa, "tecc is differ");
    }
    quitf(_ok, "OK");
}
