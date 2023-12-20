#include <cassert>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ll = long long;
template <typename T>
using V = vector<T>;
template <typename T>
using VV = V<V<T>>;

struct E
{
    int index, to;
    ll dist;
};

/**
Information of mst
*/
struct MstInfo
{
    ll cost;    /// mst cost
    V<int> res; /// edge list
};

/// calc mst by Prim's algorithm
MstInfo prim(const VV<E> &g, const int start)
{
    int n = int(g.size());
    V<bool> vis(n);
    auto comp = [&](E a, E b)
    {
        if (a.dist == b.dist)
            return a.index > b.index;

        return a.dist > b.dist;
    };
    priority_queue<E, vector<E>, decltype(comp)> pq{comp};

    vis[start] = true;
    for (auto &e : g[start])
    {
        pq.push(e);
    }
    ll cost = 0;
    V<int> res;
    while (pq.size())
    {
        auto e = pq.top();
        pq.pop();
        if (vis[e.to])
        {
            continue;
        }
        vis[e.to] = true;
        cost += e.dist;
        res.push_back(e.index);
        for (auto &e2 : g[e.to])
        {
            if (!vis[e2.to])
                pq.push(e2);
        }
    }
    return {cost, res};
}

int main()
{
    int n, m;
    scanf("%d %d", &n, &m);

    VV<E> g(n);
    for (int i = 0; i < m; i++)
    {
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        g[a].push_back({i, b, c});
        g[b].push_back({i, a, c});
    }

    auto [cost, res] = prim(g, 0);

    printf("%lld\n", cost);
    for (int i = 0; i < n - 1; i++)
    {
        if (i != 0)
            printf(" ");
        printf("%d", res[i]);
    }
    printf("\n");

    return 0;
}
