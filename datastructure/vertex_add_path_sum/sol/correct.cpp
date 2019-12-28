#include <iostream>
#include <vector>
#include <cassert>
#include <tuple>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;


struct HL {
    V<int> _ord, _rord, big, small;  // primitive
    V<int> dps;                      // node depth(optional)
    int pc = 0;                      // path count(optional)
    V<int> pid, psz;                 // path id, size (optional)
    V<int> out;                      // [id, out[id]) is subtree(optional)
    HL(int n = 0)
        : _ord(n), _rord(n), big(n), small(n), dps(n), pid(n), out(n) {}
    int ord(int v) const { return v == -1 ? -1 : _ord[v]; }
    int rord(int i) const { return i == -1 ? -1 : _rord[i]; }
    int par(int v) const {
        v = ord(v);
        return rord(small[v] == v ? big[v] : v - 1);
    }
    int lca(int a, int b) const {
        a = ord(a);
        b = ord(b);
        while (a != b) {
            if (a > b) swap(a, b);
            if (small[b] <= a)
                break;
            else
                b = big[b];
        }
        return rord(a);
    }
    template <class F>
    void get_path(int a,
                  int b,
                  F f) const {  // aの直前までbから登る、fの引数は両閉区間
        a = ord(a);
        b = ord(b);
        while (a < b) {
            if (small[b] <= a)
                f(a + 1, b);
            else
                f(small[b], b);
            b = big[b];
        }
    }
    int to(int a, int b) {  // aからbの方向へ1移動する
        a = ord(a);
        b = ord(b);
        assert(a < b);
        while (true) {
            if (small[b] <= a)
                return rord(a + 1);
            else if (big[b] == a)
                return rord(small[b]);
            b = big[b];
        }
        assert(false);
    }
};

template <class E> struct HLExec : HL {
    const VV<E>& g;
    V<int> tch;
    int id = 0;
    HLExec(const VV<E>& _g, int r) : HL(_g.size()), g(_g), tch(g.size(), -1) {
        assert(dfs_sz(r, -1) == int(g.size()));
        dfs(r, -1);
        init_extra();
    }
    void init_extra() {
        // ord, rord, big, small以外を使わないなら不要
        int n = int(g.size());

        // dps
        dps[0] = 0;
        for (int i = 1; i < n; i++) {
            dps[i] = dps[ord(par(rord(i)))] + 1;
        }

        // pid, psz, pc
        int l = 0;
        while (l < n) {
            int r = l + 1;
            while (r < n && small[r] == l) r++;
            psz.push_back(r - l);
            for (int i = l; i < r; i++) {
                pid[i] = pc;
            }
            l = r;
            pc++;
        }

        // out
        for (int i = n - 1; i >= 0; i--) {
            out[i] = max(out[i], i + 1);
            int p = ord(par(rord(i)));
            if (p != -1) out[p] = max(out[p], out[i]);
        }
    }
    int dfs_sz(int p, int b) {
        int sz = 1, msz = -1;
        for (auto e : g[p]) {
            if (e.to == b) continue;
            int u = dfs_sz(e.to, p);
            sz += u;
            if (msz < u) tie(tch[p], msz) = make_pair(e.to, u);
        }
        return sz;
    }
    void dfs(int p, int b) {
        int q = id++, bq = ord(b);
        _ord[p] = q;
        _rord[q] = p;
        if (b == -1 || bq != q - 1) {
            small[q] = q;
            big[q] = bq;
        } else {
            small[q] = small[bq];
            big[q] = big[bq];
        }
        if (tch[p] == -1) return;
        dfs(tch[p], p);
        for (auto e : g[p]) {
            if (e.to == b || e.to == tch[p]) continue;
            dfs(e.to, p);
        }
    }
};

template <class E> HL get_hl(const VV<E>& g, int r) { return HLExec<E>(g, r); }

template <class T> struct Fenwick {
    int n;
    V<T> seg;
    Fenwick(int _n = 0) : n(_n), seg(n + 1) {}
    /// i番目の要素にxを追加する
    void add(int i, T x) {
        i++;
        while (i <= n) {
            seg[i] += x;
            i += i & -i;
        }
    }
    /// [0, i)のsum
    T sum(int i) {
        T s = 0;
        while (i > 0) {
            s += seg[i];
            i -= i & -i;
        }
        return s;
    }
    /// [a, b)のsum
    T sum(int a, int b) { return sum(b) - sum(a); }
};

int main() {
    
    int n, q;
    scanf("%d %d", &n, &q);
    V<ll> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
    }
    struct E { int to; };
    auto g = VV<E>(n);
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        g[a].push_back({b});
        g[b].push_back({a});
    }
    auto hl = get_hl(g, 0);
    auto fw = Fenwick<ll>(n);

    for (int i = 0; i < n; i++) {
        fw.add(hl.ord(i), a[i]);
    }

    for (int i = 0; i < q; i++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int p; ll x;
            scanf("%d %lld", &p, &x);
            a[p] += x;
            fw.add(hl.ord(p), x);
        } else {
            int u, v;
            scanf("%d %d", &u, &v);
            int lca = hl.lca(u, v);
            ll sm = a[lca];
            hl.get_path(lca, u, [&](int a, int b) {
                sm += fw.sum(a, b + 1);
            });
            hl.get_path(lca, v, [&](int a, int b) {
                sm += fw.sum(a, b + 1);
            });
            printf("%lld\n", sm);
        }
    }
    return 0;
}
