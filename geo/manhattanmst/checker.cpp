#include "testlib.h"
#include <vector>
#include <map>
#include <utility>

using namespace std;
using ll = long long;
using P = pair<int, int>;

struct UnionFind {
    vector<int> p, r;
    int gn;
    UnionFind(int n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b) {
        int x = group(a), y = group(b);
        if (x == y) return;  // same
        gn--;
        if (r[x] < r[y]) {
            p[x] = y;
        } else {
            p[y] = x;
            if (r[x] == r[y]) r[x]++;
        }
    }
    int group(int a) {
        if (p[a] == -1) return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) { return group(a) == group(b); }
};

ll read_ans(int n, vector<P> points, InStream& stream) {
    ll x = stream.readLong();
    ll sum = 0;
    UnionFind uf(n);
    for (int i = 0; i < n - 1; i++) {
        int u = stream.readInt(0, n - 1);
        int v = stream.readInt(0, n - 1);
        if (uf.same(u, v)) {
            stream.quit(_wa, "input isn't tree");
        }
        uf.merge(u, v);
        sum += abs(points[u].first - points[v].first);
        sum += abs(points[u].second - points[v].second);
    }

    if (x != sum) {
        stream.quitf(_wa, "X(" I64 ") isn't correct, sum = " I64, x, sum);
    }
    return x;
}

int main(int argc, char *argv[]) {
    setName("compare directed mst");
    registerTestlibCmd(argc, argv);

    // input
    int n = inf.readInt();
    vector<P> points(n);
    for (int i = 0; i < n; i++) {
        int x = inf.readInt();
        int y = inf.readInt();
        points[i] = {x, y};
    }

    ll x_ans = read_ans(n, points, ans);
    ll x_ouf = read_ans(n, points, ouf);

    if (x_ans < x_ouf) {
        quitf(_wa, "There is the better solution");
    }
    if (x_ans > x_ouf) {
        quitf(_fail, "Participate find better answer");
    }
    quitf(_ok, "OK: " I64, x_ouf);
}
