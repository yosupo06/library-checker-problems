#include "testlib.h"
#include <vector>
#include <map>

using namespace std;

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

int main(int argc, char *argv[]) {
    setName("compare directed mst");
    registerTestlibCmd(argc, argv);

    long long x_ans = ans.readLong();
    long long x_ouf = ouf.readLong();

    if (x_ans != x_ouf) {
        quitf(_wa, "Value is differ - expected '%lld', found '%lld'", x_ans, x_ouf);
    }

    // input
    using P = pair<int, int>;
    int n = inf.readInt();
    int m = inf.readInt();
    map<P, long long> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        long long c = inf.readLong();
        edges[{a, b}] = c;
    }

    long long sum = 0;
    UnionFind uf(n);
    for (int i = 1; i < n; i++) {
        int p = ouf.readInt(0, n - 1);
        ensure(!uf.same(p, i));
        sum += edges[{p, i}];
    }

    ensure(x_ouf == sum);
    quitf(_ok, "OK");
}
