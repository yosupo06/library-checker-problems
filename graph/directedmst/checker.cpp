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

ll read_ans(int n, int s, map<P, ll> edges, InStream& stream) {
    ll x = stream.readLong();
    ll sum = 0;
    UnionFind uf(n);
    for (int i = 0; i < n; i++) {
        int p = stream.readInt(0, n - 1);
        if (i == s) {
            if (p != s) {
                stream.quitf(_wa, "p_%d(root) must be %d", s, s);
            }
            continue;
        }
        if (uf.same(p, i)) {
            stream.quit(_wa, "input isn't tree");
        }
        uf.merge(p, i);
        if (!edges.count({p, i})) {
            stream.quitf(_wa, "there isn't edge (%d, %d)", p, i);
        }
        sum += edges[{p, i}];        
    }

    if (x != sum) {
        stream.quitf(_wa, "X(%lld) isn't correct, sum = %lld", x, sum);
    }
    return x;
}

int main(int argc, char *argv[]) {
    setName("compare directed mst");
    registerTestlibCmd(argc, argv);

    // input
    using P = pair<int, int>;
    int n = inf.readInt();
    int m = inf.readInt();
    int s = inf.readInt();
    map<P, ll> edges;
    for (int i = 0; i < m; i++) {
        int a = inf.readInt();
        int b = inf.readInt();
        ll c = inf.readLong();
        edges[{a, b}] = c;
    }

    ll x_ans = read_ans(n, s, edges, ans);
    ll x_ouf = read_ans(n, s, edges, ouf);

    if (x_ans < x_ouf) {
        quitf(_wa, "There is the better solution");
    }
    if (x_ans > x_ouf) {
        quitf(_fail, "Participate find better answer");
    }
    quitf(_ok, "OK: %lld", x_ouf);
}
