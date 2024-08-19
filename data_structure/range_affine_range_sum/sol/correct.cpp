#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using uint = unsigned int;
using ll = long long;
using ull = unsigned long long;
constexpr ll TEN(int n) { return (n == 0) ? 1 : 10 * TEN(n - 1); }
template <class T> using V = vector<T>;
template <class T> using VV = V<V<T>>;

template <class D, class L, class OpDD, class OpDL, class OpLL> struct SegTree {
    D e_d;
    L e_l;
    OpDD op_dd;
    OpDL op_dl;
    OpLL op_ll;
    int sz, lg;  //(2^lgに拡張後の)サイズ, lg
    V<D> d;
    V<L> lz;

    SegTree(const V<D>& v,
            D _e_d,
            L _e_l,
            OpDD _op_dd,
            OpDL _op_dl,
            OpLL _op_ll)
        : e_d(_e_d), e_l(_e_l), op_dd(_op_dd), op_dl(_op_dl), op_ll(_op_ll) {
        int n = int(v.size());
        lg = 1;
        while ((1 << lg) < n) lg++;
        sz = 1 << lg;
        d = V<D>(2 * sz, e_d);
        lz = V<L>(2 * sz, e_l);
        for (int i = 0; i < n; i++) d[sz + i] = v[i];
        for (int i = sz - 1; i >= 0; i--) {
            update(i);
        }
    }

    void all_add(int k, L x) {
        d[k] = op_dl(d[k], x);
        lz[k] = op_ll(lz[k], x);
    }
    void push(int k) {
        all_add(2 * k, lz[k]);
        all_add(2 * k + 1, lz[k]);
        lz[k] = e_l;
    }
    void update(int k) { d[k] = op_dd(d[2 * k], d[2 * k + 1]); }

    void set(int p, D x) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        d[p] = x;
        for (int i = 1; i <= lg; i++) update(p >> i);
    }

    void add(int a, int b, L x, int l, int r, int k) {
        if (b <= l || r <= a) return;
        if (a <= l && r <= b) {
            all_add(k, x);
            return;
        }
        push(k);
        int mid = (l + r) / 2;
        add(a, b, x, l, mid, 2 * k);
        add(a, b, x, mid, r, 2 * k + 1);
        update(k);
    }
    void add(int a, int b, L x) { add(a, b, x, 0, sz, 1); }

    D single(int p) {
        p += sz;
        for (int i = lg; i >= 1; i--) push(p >> i);
        return d[p];
    }

    D sum(int a, int b, int l, int r, int k) {
        if (b <= l || r <= a) return e_d;
        if (a <= l && r <= b) return d[k];
        push(k);
        int mid = (l + r) / 2;
        return op_dd(sum(a, b, l, mid, 2 * k), sum(a, b, mid, r, 2 * k + 1));
    }
    D sum(int a, int b) { return sum(a, b, 0, sz, 1); }
};

template <class D, class L, class OpDD, class OpDL, class OpLL>
SegTree<D, L, OpDD, OpDL, OpLL> get_seg(V<D> v,
                                        D e_d,
                                        L e_l,
                                        OpDD op_dd,
                                        OpDL op_dl,
                                        OpLL op_ll) {
    return SegTree<D, L, OpDD, OpDL, OpLL>(v, e_d, e_l, op_dd, op_dl, op_ll);
}

const ll MOD = 998244353;

int main() {
    int n, q;
    scanf("%d %d", &n, &q);
    struct F {
        ll a, b;
    };
    using P = pair<ll, int>;
    vector<P> a(n);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i].first);
        a[i].second = 1;
    }
    auto segtree =
        get_seg(a, {0LL, 0}, F{1, 0},
                [&](P l, P r) {
                    return P{(l.first + r.first) % MOD, l.second + r.second};
                },
                [&](P l, F r) {
                    return P{(l.first * r.a + l.second * r.b) % MOD, l.second};
                },
                [&](F l, F r) {
                    // x
                    // -> l.a * x + l.b
                    // -> r.a(l.a * x + l.b) + r.b
                    ll na = l.a * r.a % MOD;
                    ll nb = (l.b * r.a + r.b) % MOD;
                    return F{na, nb};
                });

    for (int ph = 0; ph < q; ph++) {
        int ty;
        scanf("%d", &ty);
        if (ty == 0) {
            int l, r;
            ll c, d;
            scanf("%d %d %lld %lld", &l, &r, &c, &d);
            segtree.add(l, r, {c, d});
        } else {
            int l, r;
            scanf("%d %d", &l, &r);
            printf("%lld\n", segtree.sum(l, r).first);
        }
    }
    return 0;
}
