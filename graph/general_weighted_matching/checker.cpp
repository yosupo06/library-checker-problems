#include "testlib.h"

using namespace std;

using P = pair<int, int>;
using M = map<P, int>;

P read_ans(int n, const M& edges, InStream& stream) {
    int matching_edges = stream.readInt(0, n);
    int matching_cost = stream.readInt(0, 0x7fffffff);
    vector<bool> used(n);
    int cost = 0;
    for (int i = 0; i < matching_edges; i++) {
        int u = stream.readInt(0, n - 1);
        int v = stream.readInt(0, n - 1);
        if (used[u]) {
            stream.quitf(_wa, "reuse %d", u);
        }
        if (used[v]) {
            stream.quitf(_wa, "reuse %d", v);
        }
        used[u] = used[v] = true;
        if (u > v) {
            swap(u, v);
        }
        auto it = edges.find({u, v});
        if (it == edges.cend()) {
            stream.quitf(_wa, "there isn't edge (%d, %d)", u, v);
        }
        cost += it->second;
    }
    if (cost != matching_cost) {
        stream.quitf(_wa, "computed cost (%d) isn't equal output cost (%d)", cost, matching_cost);
    }
    return {cost, matching_edges};
}

int main(int argc, char *argv[]) {
    setName("checker for general_weighted_matching");
    registerTestlibCmd(argc, argv);
    int n = inf.readInt();
    int m = inf.readInt();
    M edges;
    for (int i = 0; i < m; i++) {
        int u = inf.readInt();
        int v = inf.readInt();
        if (u > v) {
            swap(u, v);
        }
        int w = inf.readInt();
        edges.insert({{u, v}, w});
    }
    auto x_ans = read_ans(n, edges, ans);
    auto x_ouf = read_ans(n, edges, ouf);
    if (x_ans.first < x_ouf.first) {
        quitf(_fail, "Participate find better answer....");
    } else if (x_ans.first > x_ouf.first) {
        quitf(_wa, "There is the better solution");
    }
    quitf(_ok, "OK: %d matchings (cost = %d)", x_ans.second, x_ans.first);
}
