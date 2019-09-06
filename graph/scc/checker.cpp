#include <algorithm>
#include "testlib.h"

using namespace std;

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();


    int k_ans = ans.readInt(1, n);
    int k_ouf = ouf.readInt(1, n);
    if (k_ans != k_ouf) {
        quitf(_wa, "# of scc is differ - expected: '%d', found: '%d'", k_ans, k_ouf);
    }

    vector<vector<int>> sccs_ans(k_ans), sccs_ouf(k_ouf);
    for (int i = 0; i < k_ans; i++) {
        int l = ans.readInt(1, n);
        sccs_ans[i] = vector<int>(l);
        for (int j = 0; j < l; j++) {
            sccs_ans[i][j] = ans.readInt();
        }
        sort(sccs_ans[i].begin(), sccs_ans[i].end());
    }

    vector<int> pos_ouf(n, -1);
    for (int i = 0; i < k_ouf; i++)
    {
        int l = ouf.readInt(1, n);
        sccs_ouf[i] = vector<int>(l);
        for (int j = 0; j < l; j++) {
            sccs_ouf[i][j] = ouf.readInt();
            ensure(pos_ouf[sccs_ouf[i][j]] == -1);
            pos_ouf[sccs_ouf[i][j]] = i;
        }
        sort(sccs_ouf[i].begin(), sccs_ouf[i].end());
    }

    for (int i = 0; i < m; i++) {
        int u = inf.readInt(0, n - 1);
        int v = inf.readInt(0, n - 1);
        ensure(pos_ouf[u] <= pos_ouf[v]);
    }

    sort(sccs_ans.begin(), sccs_ans.end());
    sort(sccs_ouf.begin(), sccs_ouf.end());

    ensure(sccs_ans == sccs_ouf);

    quitf(_ok, "OK");
}
