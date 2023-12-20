#include "testlib.h"
#include <vector>
#include <map>
#include <utility>

using namespace std;
using ll = long long;

struct E
{
    int a, b;
    ll dist;
};

struct UnionFind
{
    vector<int> p, r;
    int gn;
    UnionFind(int n = 0) : p(n, -1), r(n, 1), gn(n) {}
    void merge(int a, int b)
    {
        int x = group(a), y = group(b);
        if (x == y)
            return; // same
        gn--;
        if (r[x] < r[y])
        {
            p[x] = y;
        }
        else
        {
            p[y] = x;
            if (r[x] == r[y])
                r[x]++;
        }
    }
    int group(int a)
    {
        if (p[a] == -1)
            return a;
        return p[a] = group(p[a]);
    }
    bool same(int a, int b) { return group(a) == group(b); }
};

ll read_ans(int n, int m, vector<E> edges, InStream &stream)
{
    ll x = stream.readLong();
    ll sum = 0;
    UnionFind uf(n);
    for (int i = 0; i < n - 1; i++)
    {
        int ei = stream.readInt(0, m);
        auto e = edges[ei];
        if (uf.same(e.a, e.b))
        {
            stream.quit(_wa, "input isn't tree");
        }
        uf.merge(e.a, e.b);
        sum += e.dist;
    }

    if (x != sum)
    {
        stream.quitf(_wa, "X(" I64 ") isn't correct, sum = " I64, x, sum);
    }
    return x;
}

int main(int argc, char *argv[])
{
    setName("compare mst");
    registerTestlibCmd(argc, argv);

    // input
    int n = inf.readInt();
    int m = inf.readInt();
    vector<E> edges(m);
    for (int i = 0; i < m; i++)
    {
        int a = inf.readInt();
        int b = inf.readInt();
        ll c = inf.readLong();
        edges[i] = {a, b, c};
    }

    ll x_ans = read_ans(n, m, edges, ans);
    ll x_ouf = read_ans(n, m, edges, ouf);

    if (x_ans < x_ouf)
    {
        quitf(_wa, "There is the better solution");
    }
    if (x_ans > x_ouf)
    {
        quitf(_fail, "Participate find better answer");
    }
    quitf(_ok, "OK: " I64, x_ouf);
}
