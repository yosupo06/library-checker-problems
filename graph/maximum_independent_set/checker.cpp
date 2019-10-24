#include <vector>
#include "testlib.h"

using namespace std;

using P = pair<int, int>;

int read_ans(int n, vector<P> edges, InStream& stream) {
    int x = stream.readInt(0, n);
    vector<bool> used(n);
    for (int i = 0; i < x; i++) {
        int u = stream.readInt(0, n - 1);
        if (used[u]) {
            stream.quitf(_wa, "reuse %d", u);
        }
        used[u] = true;
    }
    for (auto edge: edges) {
        if (used[edge.first] && used[edge.second]) {
            stream.quitf(_wa, "This isn't independent set");
        }
    }
    return x;
}

int main(int argc, char *argv[]) {
    setName("compare sequences of tokens");
    registerTestlibCmd(argc, argv);

    int n = inf.readInt();
    int m = inf.readInt();
    vector<P> edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        edges.push_back({u, v});
    }
    int x_ans = read_ans(n, edges, ans);
    int x_ouf = read_ans(n, edges, ouf);

    if (x_ans < x_ouf) {
        quitf(_fail, "Participate find better answer....");
    } else if (x_ans > x_ouf) {
        quitf(_wa, "There is the better solution");
    }
    quitf(_ok, "OK: %d vertexes", x_ans);
}
