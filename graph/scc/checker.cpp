#include <algorithm>
#include "testlib.h"

using namespace std;
using P = pair<int, int>;

// check and return scc
vector<vector<int>> read_ans(int n, vector<P> edges, InStream& stream) {
    int k = stream.readInt(1, n);
    vector<vector<int>> sccs(k);
    vector<int> pos(n, -1);
    for (int i = 0; i < k; i++) {
        int l = stream.readInt(1, n);
        sccs[i] = vector<int>(l);
        for (int j = 0; j < l; j++) {
            sccs[i][j] = stream.readInt(0, n - 1);
            if (pos[sccs[i][j]] != -1) {
                stream.quitf(_wa, "twice used vertex %d", sccs[i][j]);
            }
            pos[sccs[i][j]] = i;
        }
        sort(sccs[i].begin(), sccs[i].end());
    }
    for (auto edge: edges) {
        int u = edge.first, v = edge.second;
        if (pos[u] > pos[v]) {
            stream.quitf(_wa, "%d is later than %d, but there is an edge (%d, %d)", u, v, u, v);
        }
    }
    return sccs;
}

int main(int argc, char *argv[]) {
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<P> edges(m);
    for (int i = 0; i < m; i++) {
        edges[i].first = inf.readInt();
        edges[i].second = inf.readInt();
    }

    auto sccs_ans = read_ans(n, edges, ans);
    auto sccs_ouf = read_ans(n, edges, ouf);
    int k_ans = int(sccs_ans.size());
    int k_ouf = int(sccs_ouf.size());
    if (k_ans != k_ouf) {
        quitf(_wa, "# of scc is differ - expected: '%d', found: '%d'", k_ans, k_ouf);
    }

    sort(sccs_ans.begin(), sccs_ans.end());
    sort(sccs_ouf.begin(), sccs_ouf.end());

    if (sccs_ans != sccs_ouf) {
        quitf(_wa, "scc is differ");
    }
    quitf(_ok, "OK");
}
