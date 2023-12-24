#include <iostream>
#include <set>
#include <utility>
#include "testlib.h"
#include "params.h"
#include <queue>

using namespace std;

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
    int groupCount()
    {
        return gn;
    }
};

int main()
{
    registerValidation();

    int n = inf.readInt(1, N_MAX);
    inf.readSpace();
    int m = inf.readInt(n - 1, N_MAX);
    inf.readChar('\n');

    UnionFind uf(n);
    for (int i = 0; i < m; i++)
    {
        int a = inf.readInt(0, n - 1);
        inf.readSpace();
        int b = inf.readInt(0, n - 1);
        inf.readSpace();
        inf.readInt(0, C_MAX);
        inf.readChar('\n');

        uf.merge(a, b);
    }
    inf.readEof();

    ensure(uf.groupCount() == 1);
    return 0;
}
