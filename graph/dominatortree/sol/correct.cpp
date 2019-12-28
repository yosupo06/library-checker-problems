#include <cassert>
#include <iostream>
#include <memory>
#include <tuple>
#include <vector>
#include <numeric>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

struct Dominator {
    V<int> idom;
};

template <class E> struct DominatorExec : Dominator {
    V<int> sdom;

    V<int> par, ord, vis;
    int ord_c = 0;
    const VV<E>& g;
    void dfs(int p) {
        vis.push_back(p);
        ord[p] = ord_c++;
        for (auto e : g[p]) {
            int d = e.to;
            if (ord[d] != -1) continue;
            par[d] = p;
            dfs(d);
        }
    }

    // unionfind
    V<int> uf_par, min_v;  // parent, min sdom's v
    int compress(int a) {
        int pa = uf_par[a];
        if (pa != -1) {
            compress(pa);
            if (ord[sdom[min_v[a]]] > ord[sdom[min_v[pa]]]) {
                min_v[a] = min_v[pa];
            }
            if (uf_par[pa] != -1) uf_par[a] = uf_par[pa];
        }
        return min_v[a];
    }

    DominatorExec(const VV<E>& _g, const VV<E>& rg, int s) : g(_g) {
        int n = (int)(g.size());

        par = ord = V<int>(n, -1);
        dfs(s);

        // uf init
        uf_par = V<int>(n, -1);
        min_v = V<int>(n);
        iota(min_v.begin(), min_v.end(), 0);

        idom = V<int>(n, -1);
        sdom = min_v;

        V<int> up(n);
        VV<int> bucket(n);
        for (int ph = ord_c - 1; ph >= 1; ph--) {
            int u = vis[ph];
            for (E e : rg[u]) {
                if (ord[e.to] == -1) continue;
                sdom[u] = vis[min(ord[sdom[u]], ord[sdom[compress(e.to)]])];
            }
            bucket[sdom[u]].push_back(u);
            for (int v : bucket[par[u]]) {
                up[v] = compress(v);
            }
            bucket[par[u]].clear();
            uf_par[u] = par[u];  // uf merge
        }

        for (int ph = 1; ph < ord_c; ph++) {
            int u = vis[ph], v = up[u];
            if (sdom[u] == sdom[v])
                idom[u] = sdom[u];
            else
                idom[u] = idom[v];
        }
    }
};

template <class E>
Dominator get_dominator(const VV<E>& _g, const VV<E>& _rg, int s) {
    return DominatorExec<E>(_g, _rg, s);
}

int main() {

    int n, m, s;
    scanf("%d %d %d", &n, &m, &s);

    struct E { int to; };
    VV<E> g(n), rg(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back({b});
        rg[b].push_back({a});
    }

    auto domi = get_dominator(g, rg, s);

    domi.idom[s] = s;

    for (int i = 0; i < n; i++) {
        cout << domi.idom[i];
        if (i != n - 1) cout << " ";
    }
    printf("\n");
    return 0;
}
