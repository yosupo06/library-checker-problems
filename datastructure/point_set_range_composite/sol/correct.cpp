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

const ll MOD = 998244353;

int main() {

    int n, q;
    cin >> n >> q;
    struct F {
        ll a, b;
    };


    vector<F> f(n);
    for (int i = 0; i < n; i++) {
        cin >> f[i].a >> f[i].b;
    }
    auto segtree = get_simple_seg(f, {1, 0}, [&](F l, F r) {
        // x -> l.a * x + l.b -> r.a(l.a * x + l.b) + r.b
        ll na = l.a * r.a % MOD;
        ll nb = (l.b * r.a + r.b) % MOD;
        return F{na, nb};
    });

    for (int ph = 0; ph < q; ph++) {
        int ty;
        cin >> ty;
        if (ty == 0) {
            int p;
            ll c, d;
            cin >> p >> c >> d;
            segtree.set(p, {c, d});
        } else {
            int l, r;
            ll x;
            cin >> l >> r >> x;
            auto f = segtree.sum(l, r);
            cout << (f.a * x + f.b) % MOD << "\n";
        }
    }
    return 0;
}
