// Offline solution

#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include "modint.hpp"
using namespace std;

using i32 = int;
using i64 = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template<typename T> using vec = vector<T>;

template<typename PT, typename M, u32 K = tuple_size<PT>::value>
struct LazyKDTree
{

#define KDT_MIS make_index_sequence<K>{}
#define KDT_ARGS const PT& a, const PT& b, index_sequence<Is...>

    template <size_t... Is> 
    PT min_pt(KDT_ARGS) {return { min(std::get<Is>(a), std::get<Is>(b))... };}
    template <size_t... Is> 
    PT max_pt(KDT_ARGS) {return { max(std::get<Is>(a), std::get<Is>(b))... };}

    template <size_t... Is> 
    bool cle_pt_impl(KDT_ARGS) 
        { return ((std::get<Is>(a) <= std::get<Is>(b)) && ...); }
    bool cle_pt(const PT& a, const PT& b){ return cle_pt_impl(a, b, KDT_MIS); }

    using MS = typename M::MS;
    using MA = typename M::MA;
    using S = typename MS::S;
    using A = typename MA::S;

    struct Node
    {
        // Vector sp -> ep describes the hypercube.
        PT sp, ep;
        S val;
        Node(const PT &_sp, const PT &_tp, const S &s = M::un()): 
            sp(_sp), ep(_tp), val(s) { }
        Node() { }
    };

    u32 n;
    vec<A> t;
    vec<Node> d;
    vec<u32> rnk;

    LazyKDTree(): n() { }
    LazyKDTree(u32 _n, const vec<PT> &p, const vec<S> &s)
        : n(_n), t(), d(), rnk(n)
    {
        u32 m = 1;
        while (m < n) m += m;
        t.resize(m, MA::un());
        d.resize(m * 2);
        vec<u32> idx(n);
        for (u32 i = 0; i < n; i++) idx[i] = i;
        build_rec<0>(p, s, idx, 0, n, 1);
    }

    void apply_at(u32 x, const A& a, u32 len)
    {
        d[x].val = M::act(d[x].val, a, len);
        if (len > 1) t[x] = MA::op(t[x], a);
    }
    void push_down(u32 x, u32 l, u32 r)
    {
        if (t[x] == MA::un()) return ;
        apply_at(x * 2, t[x], l);
        apply_at(x * 2 + 1, t[x], r);
        t[x] = MA::un();
    }

    // Vector st -> ed describes a hypercube.
    S prod(const PT &st, const PT &ed) { return prod_rec(st, ed, 0, n, 1); }
    S get(u32 x) { return get_rec(x, 0, n, 1); }
    void set(u32 x, const S &v) { set_rec(rnk[x], v, 0, n, 1); }
    void apply(const PT &st, const PT &ed, const A &a) 
    { 
        apply_rec(st, ed, a, 0, n, 1);
    }
    template<typename RIt>
    void print_val(RIt o) 
    {
        vec<u32> idx(n);
        for (u32 i = 0; i < n; i++) idx[rnk[i]] = i;
        print_rec(idx, 0, n, 1, o);
    }

    template<u32 D>
    void build_rec(const vec<PT> &p, const vec<S> &s, 
        vec<u32> &idx, u32 l, u32 r, u32 x)
    {
        if (l + 1 == r) {
            u32 idn = idx[l];
            d[x] = {p[idn], p[idn], s[idn]};
            rnk[idn] = l;
            return ;
        }
        u32 mid = (l + r) >> 1;
        nth_element(idx.data() + l, idx.data() + mid, idx.data() + r, 
            [&p](u32 a, u32 b) 
            { return std::get<D>(p[a]) < std::get<D>(p[b]); });
        build_rec<(D + 1) % K>(p, s, idx, l, mid, x * 2);
        build_rec<(D + 1) % K>(p, s, idx, mid, r, x * 2 + 1);
        d[x].sp = min_pt(d[x * 2].sp, d[x * 2 + 1].sp, KDT_MIS);
        d[x].ep = max_pt(d[x * 2].ep, d[x * 2 + 1].ep, KDT_MIS);
        d[x].val = MS::op(d[x * 2].val, d[x * 2 + 1].val);
    }

private:

    S prod_rec(const PT &st, const PT &ed, u32 l, u32 r, u32 x)
    {
        if (cle_pt(st, d[x].sp) && cle_pt(d[x].ep, ed)) return d[x].val;
        if (!cle_pt(d[x].sp, ed) || !cle_pt(st, d[x].ep)) return MS::un();
        u32 mid = (l + r) >> 1;
        push_down(x, mid - l, r - mid);
        return MS::op(prod_rec(st, ed, l, mid, x * 2), 
                     prod_rec(st, ed, mid, r, x * 2 + 1));
    }

    void apply_rec(const PT &st, const PT &ed, const A &a, u32 l, u32 r, u32 x)
    {
        if (cle_pt(st, d[x].sp) && cle_pt(d[x].ep, ed)) {
            apply_at(x, a, r - l);
            return ;
        }
        if (!cle_pt(d[x].sp, ed) || !cle_pt(st, d[x].ep)) return ;
        u32 mid = (l + r) >> 1;
        push_down(x, mid - l, r - mid);
        apply_rec(st, ed, a, l, mid, x * 2);
        apply_rec(st, ed, a, mid, r, x * 2 + 1);
        d[x].val = MS::op(d[x * 2].val, d[x * 2 + 1].val);
    }

    void set_rec(u32 p, const S &v, u32 l, u32 r, u32 x)
    {
        if (l + 1 == r) {
            d[x].val = v;
            return ;
        }
        u32 mid = (l + r) >> 1;
        push_down(x, mid - l, r - mid);
        if (p < mid) set_rec(p, v, l, mid, x * 2);
        else set_rec(p, v, mid, r, x * 2 + 1);
        d[x].val = MS::op(d[x * 2].val, d[x * 2 + 1].val);
    }

    S get_rec(u32 p, u32 l, u32 r, u32 x)
    {
        if (l + 1 == r) return d[x].val;
        u32 mid = (l + r) >> 1;
        push_down(x, mid - l, r - mid);
        if (p < mid) return get_rec(p, l, mid, x * 2);
        return get_rec(p, mid, r, x * 2 + 1);
    }

    template<typename RIt>
    void print_rec(const vec<u32> &idx, u32 l, u32 r, u32 x, RIt o)
    {
        if (l + 1 == r) {
            o[idx[l]] = d[x].val;
            return ;
        }
        u32 mid = (l + r) >> 1;
        push_down(x, mid - l, r - mid);
        print_rec(idx, l, mid, x * 2, o);
        print_rec(idx, mid, r, x * 2 + 1, o);
    }

#undef KDT_MIS
#undef KDT_ARGS
};

using mint = atcoder::modint998244353;

struct MonoidSum
{
    using S = pair<mint, u32>;
    static S op(S a, S b) { return {a.first + b.first, a.second + b.second}; }
    static S un() { return S(); }
};
struct MonoidAffine
{
    using S = pair<mint, mint>;
    static S op(const S &a, const S &b)
    {
        return {a.first * b.first, a.second * b.first + b.second};
    }
    static S un() { return {1, 0}; }
};
struct ActedMonoid
{
    using MS = MonoidSum;
    using MA = MonoidAffine;
    static pair<mint, u32> 
        act(const pair<mint, u32> v, const pair<mint, mint> &a, u32)
    {
        return {v.first * a.first + v.second * a.second, v.second};
    }
};

struct Query
{
    u32 op, a, b, c, d, e, f;
};

signed main() 
{
    // ios::sync_with_stdio(false);
    // cin.tie(0), cout.tie(0);
    using Point = pair<u32, u32>;
    u32 n, q;
    // cin >> n >> q;
	scanf("%u %u", &n, &q);
    vec<Point> pt;
    vec<pair<mint, u32>> v;
    vec<Query> qr(q);
    for (u32 i = 0, x, y, z; i < n; i++) {
        // cin >> x >> y >> z;
		scanf("%u %u %u", &x, &y, &z);
        pt.emplace_back(x, y);
        v.emplace_back(z, 1);
    }
    for (auto &[op, a, b, c, d, e, f]: qr) {
        // cin >> op;
		scanf("%u", &op);
        if (op == 0) {
            // cin >> a >> b >> c;
			scanf("%u %u %u", &a, &b, &c);
            pt.emplace_back(a, b);
            v.emplace_back(0, 0);
            a = pt.size() - 1, b = c;
        }
        else if (op == 1) {
			// cin >> a >> b;
			scanf("%u %u", &a, &b);
		}
        else if (op == 2) {
			// cin >> a >> b >> c >> d;
			scanf("%u %u %u %u", &a, &b, &c, &d);
		}
        else {
			// cin >> a >> b >> c >> d >> e >> f;
			scanf("%u %u %u %u %u %u", &a, &b, &c, &d, &e, &f);
		}
    }
    LazyKDTree<Point, ActedMonoid> t(pt.size(), pt, v);
    for (auto [op, a, b, c, d, e, f]: qr) {
        if (op <= 1) t.set(a, {b, 1});
        else if (op == 2) {
            // cout << t.prod({a, b}, {c - 1, d - 1}).first.val() << '\n';
			printf("%u\n", t.prod({a, b}, {c - 1, d - 1}).first.val());
        }
        else t.apply({a, b}, {c - 1, d - 1}, {e, f});
    }
    return 0;
}