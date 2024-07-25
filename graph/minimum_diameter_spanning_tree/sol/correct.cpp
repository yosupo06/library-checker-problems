#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <queue>
#include <map>
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template<typename T> using vec = vector<T>;
using edge = pair<u32, u32>;

struct SSSPNode
{
    u32 x, y;
    u64 d;
    SSSPNode(u32 _x, u32 _y, u64 _d): x(_x), y(_y), d(_d) { }
    bool operator<(const SSSPNode &t) const { return d > t.d; }
};

vec<pair<u64, u32>> sssp(u32 n, u32 s, const vec<vec<edge>> &g)
{
    vec<pair<u64, u32>> res(n, {1e18, s});
    vec<bool> vis(n);
    static priority_queue<SSSPNode> pq;
    pq.emplace(s, s, 0);
    while (!pq.empty()) {
        auto [x, y, d] = pq.top();
        pq.pop();
        if (vis[x]) continue;
        vis[x] = true;
        res[x] = {d, y};
        for (auto [v, w]: g[x]) if (!vis[v]) {
            pq.emplace(v, x, d + w);
        }
    }
    return res;
}

vec<vec<u64>> apsp(u32 n, const vec<vec<edge>> &g)
{
    vec<vec<u64>> res(n, vec<u64>(n));
    for (u32 i = 0; i < n; i++) {
        auto dis(sssp(n, i, g));
        for (u32 j = 0; j < n; j++) res[i][j] = dis[j].first;
    }
    return res;
}


pair<u64, vec<edge>> mdst(u32 n, vec<vec<edge>> g)
{
    for (u32 i = 0; i < n; i++) {
        for (auto &[_, w]: g[i]) w *= 2;
    }
    auto dis(apsp(n, g));
    vec<vec<u32>> rnk(n, vec<u32>(n));
    u64 ansp = 1e18;
    u32 srcp = 0;
    for (u32 i = 0; i < n; i++) {
        for (u32 j = 0; j < n; j++) rnk[i][j] = j;
        sort(rnk[i].begin(), rnk[i].end(), 
            [i, &dis](u32 a, u32 b) { return dis[i][a] > dis[i][b]; });
        u64 vi = dis[i][rnk[i][0]] * 2;
        if (ansp > vi) {
            ansp = vi;
            srcp = i;
        }
    }
    u64 anse = 1e18;
    u32 srcu = 0, srcv = 0, disu = 0, disv = 0;
    for (u32 u = 0; u < n; u++) {
        for (auto [v, w]: g[u]) if (v > u) {
            u32 y = rnk[u][0];
            for (u32 x: rnk[u]) {
                // >= and > are both OK.
                // Because when dis[v][x] == dis[v][y], best abs center 
                // is at a vertice instead of an edge.
                if (dis[v][x] > dis[v][y]) {
                    u64 dn = dis[v][y] + dis[u][x] + w;
                    if (dn < anse) {
                        anse = dn;
                        srcu = u, srcv = v;
                        disu = dn / 2 - dis[u][x];
                        disv = w - disu;
                    }
                    y = x;
                }
            }
        }
    }
    u64 ans, core;
    if (anse < ansp) {
        ans = anse;
        core = n;
        g.emplace_back();
        g.back().emplace_back(srcu, disu);
        g.back().emplace_back(srcv, disv);
    }
    else ans = ansp, core = srcp;
    auto t(sssp(n + 1, core, g));
    vec<edge> scheme;
    if (anse < ansp) {
        for (u32 i = 0; i < n; i++) {
            if (i != srcu && i != srcv) {
                scheme.emplace_back(i, t[i].second);
            }
        }
        scheme.emplace_back(srcu, srcv);
    }
    else {
        for (u32 i = 0; i < n; i++) if (i != core) {
            scheme.emplace_back(i, t[i].second);
        }
    }
    return {ans / 2, (scheme)};
}

signed main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    u32 n, m;
    cin >> n >> m;
    vec<vec<edge>> g(n);
    vec<u32> c(m);
    map<edge, u32> id;
    for (u32 i = 0, u, v, w; i < m; i++) {
        cin >> u >> v >> w;
        edge nw = {min(u, v), max(u, v)};
        if (!id.count(nw) || c[id[nw]] > w) {
            id[nw] = i;
        }
        c[i] = w;
        g[u].emplace_back(v, w);
        g[v].emplace_back(u, w);
    }
    auto [ans, sch] = mdst(n, std::move(g));
    cout << ans << endl;
    for (auto [u, v]: sch) {
        cout << id[{min(u, v), max(u, v)}] << ' ';
    }
    cout << endl;
    return 0;
}