#include <iostream>
#include <vector>
#include <cassert>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

struct HL {
    // inside index of HL
    struct I {
        int i;
    };
    V<int> _ord;          // int -> I
    V<int> _rord;         // I -> int
    V<int> _big, _small;  // I -> I
    // optionals
    V<int> dps;       // node depth(int -> int)
    int pc = 0;       // path count(optional)
    V<int> pid, psz;  // path id, size (optional)
    V<int> _out;      // ouv[i] is end of subtree(I -> I)
    HL() {}
    HL(size_t n)
        : _ord(n), _rord(n), _big(n), _small(n), dps(n), pid(n), _out(n) {}
    I ord(int v) const { return v == -1 ? I{-1} : I{_ord[v]}; }
    int rord(I i) const { return i.i == -1 ? -1 : _rord[i.i]; }
    I par(I i) const { return I{_small[i.i] == i.i ? _big[i.i] : i.i - 1}; }
    I subtree_out(int v) const { return I{_out[ord(v).i]}; };
    int par(int v) const { return rord(par(ord(v))); }
    int lca(int a, int b) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai != bi) {
            if (ai > bi) swap(ai, bi);
            if (_small[bi] <= ai)
                break;
            else
                bi = _big[bi];
        }
        return rord(I{ai});
    }
    // aの直前までbから登る、f(I, I)の引数は両閉区間
    template <class F> void get_path(int a, int b, F f) const {
        int ai = ord(a).i;
        int bi = ord(b).i;
        while (ai < bi) {
            if (_small[bi] <= ai)
                f(I{ai + 1}, I{bi});
            else
                f(I{_small[bi]}, I{bi});
            bi = _big[bi];
        }
    }
    int to(int a, int b) {  // aからbの方向へ1移動する
        int ai = ord(a).i;
        int bi = ord(b).i;
        assert(ai < bi);
        while (true) {
            if (_small[bi] <= ai)
                return rord(I{ai + 1});
            else if (_big[bi] == ai)
                return rord(I{_small[bi]});
            bi = _big[bi];
        }
        assert(false);
    }
    int dist(int a, int b) const {
        int c = lca(a, b);
        return dps[a] + dps[b] - 2 * dps[c];
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
        dps[rord(I{0})] = 0;
        for (int i = 1; i < n; i++) {
            dps[rord(I{i})] = dps[rord(par(I{i}))] + 1;
        }

        // pid, psz, pc
        int l = 0;
        while (l < n) {
            int r = l + 1;
            while (r < n && _small[r] == l) r++;
            psz.push_back(r - l);
            for (int i = l; i < r; i++) {
                pid[i] = pc;
            }
            l = r;
            pc++;
        }

        // out
        for (int i = n - 1; i >= 0; i--) {
            _out[i] = max(_out[i], i + 1);
            int p = ord(par(rord(I{i}))).i;
            if (p != -1) _out[p] = max(_out[p], _out[i]);
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
        int q = id++, bq = ord(b).i;
        _ord[p] = q;
        _rord[q] = p;
        if (b == -1 || bq != q - 1) {
            _small[q] = q;
            _big[q] = bq;
        } else {
            _small[q] = _small[bq];
            _big[q] = _big[bq];
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

template <class D, class Op> struct SimpleSeg {
    D e;
    Op op;
    int sz, lg;  // size(extended to 2^i), lg
    V<D> d;

    SimpleSeg(const V<D>& v, D _e, Op _op) : e(_e), op(_op) {
        int n = int(v.size());
        lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d = V<D>(2 * sz, e);
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 0; i--) {
            update(i);
        }
    }

    void update(int k) { d[k] = op(d[2 * k], d[2 * k + 1]); }

    void set(int p, D x) {
        p += sz;
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    D single(int p) { return d[p + sz]; }

    D sum(int a, int b) {
        D sml = e, smr = e;
        a += sz;
        b += sz;

        while (a < b) {
            if (a & 1) sml = op(sml, d[a++]);
            if (b & 1) smr = op(d[--b], smr);
            a >>= 1;
            b >>= 1;
        }
        return op(sml, smr);
    }
};

template <class D, class Op>
SimpleSeg<D, Op> get_simple_seg(V<D> v, D e, Op op) {
    return SimpleSeg<D, Op>(v, e, op);
}

template <uint MD> struct ModInt {
    using M = ModInt;
    const static M G;
    uint v;
    ModInt(ll _v = 0) { set_v(uint(_v % MD + MD)); }
    M& set_v(uint _v) {
        v = (_v < MD) ? _v : _v - MD;
        return *this;
    }
    explicit operator bool() const { return v != 0; }
    M operator-() const { return M() - *this; }
    M operator+(const M& r) const { return M().set_v(v + r.v); }
    M operator-(const M& r) const { return M().set_v(v + MD - r.v); }
    M operator*(const M& r) const { return M().set_v(uint(ull(v) * r.v % MD)); }
    M operator/(const M& r) const { return *this * r.inv(); }
    M& operator+=(const M& r) { return *this = *this + r; }
    M& operator-=(const M& r) { return *this = *this - r; }
    M& operator*=(const M& r) { return *this = *this * r; }
    M& operator/=(const M& r) { return *this = *this / r; }
    bool operator==(const M& r) const { return v == r.v; }
    M pow(ll n) const {
        M x = *this, r = 1;
        while (n) {
            if (n & 1) r *= x;
            x *= x;
            n >>= 1;
        }
        return r;
    }
    M inv() const { return pow(MD - 2); }
    friend ostream& operator<<(ostream& os, const M& r) { return os << r.v; }
};
using Mint = ModInt<998244353>;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    struct F {
        Mint a, b;
        F operator+(const F& r) const {
            return F{a * r.a, b * r.a + r.b};
        }
    };
    F e = {Mint(1), Mint(0)};
    V<F> f(n);
    for (int i = 0; i < n; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        f[i] = {Mint(a), Mint(b)};
    }
    struct E { int to; };
    VV<E> tr(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        tr[u].push_back({v});
        tr[v].push_back({u});
    }
    auto hl = get_hl(tr, 0);

    auto seg0 = get_simple_seg(V<F>(n), e, [&](F l, F r) {
        return l + r;
    });
    auto seg1 = get_simple_seg(V<F>(n), e, [&](F l, F r) {
        return r + l;
    });
    for (int i = 0; i < n; i++) {
        seg0.set(hl.ord(i).i, f[i]);
        seg1.set(hl.ord(i).i, f[i]);
    }

    for (int ph = 0; ph < q; ph++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int p;
            int c, d;
            scanf("%d %d %d", &p, &c, &d);
            seg0.set(hl.ord(p).i, {Mint(c), Mint(d)});
            seg1.set(hl.ord(p).i, {Mint(c), Mint(d)});
        } else {
            int u, v;
            int _x;
            scanf("%d %d %d", &u, &v, &_x);
            Mint x = _x;
            int w = hl.lca(u, v);
            F sum0 = {Mint(1), Mint(0)};
            F sum1 = {Mint(1), Mint(0)};
            hl.get_path(w, u, [&](auto l, auto r) {
                sum1 = sum1 + seg1.sum(l.i, r.i + 1);
            });
            hl.get_path(hl.par(w), v, [&](auto l, auto r) {
                sum0 = seg0.sum(l.i, r.i + 1) + sum0;
            });
            F sum = sum1 + sum0;
            printf("%d\n", (sum.a * x + sum.b).v);
        }
    }
    return 0;
}
