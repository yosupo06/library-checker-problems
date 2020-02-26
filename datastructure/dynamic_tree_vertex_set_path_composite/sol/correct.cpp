#include <algorithm>
#include <cassert>
#include <cstdio>
#include <functional>
#include <stack>
#include <utility>
#include <vector>
#define REP(i, n) for (int i = 0; (i) < (int)(n); ++ (i))
#define REP3(i, m, n) for (int i = (m); (i) < (int)(n); ++ (i))
#define REP_R(i, n) for (int i = (int)(n) - 1; (i) >= 0; -- (i))
#define REP3R(i, m, n) for (int i = (int)(n) - 1; (i) >= (int)(m); -- (i))
#define ALL(x) std::begin(x), std::end(x)

template <class Monoid>
struct reversible_monoid {
    typedef typename Monoid::value_type base_type;
    typedef std::pair<base_type, base_type> value_type;
    Monoid base;
    reversible_monoid() = default;
    reversible_monoid(const Monoid & base_) : base(base_) {}
    value_type unit() const { return std::make_pair(base.unit(), base.unit()); }
    value_type mult(const value_type & a, const value_type & b) const { return std::make_pair(base.mult(a.first, b.first), base.mult(b.second, a.second)); }
    static value_type make(const base_type & x) { return std::make_pair(x, x); }
    static value_type reverse(const value_type & a) { return std::make_pair(a.second, a.first); }
    static base_type get(const value_type & a) { return a.first; }
};

/**
 * @brief Link-Cut tree (monoids without commutativity, vertex set + path get)
 * @docs data_structure/link_cut_tree.md
 * @description manages a dynamic forest of rooted trees
 * @note in each splay tree, nodes are sorted from bottom to top. the rightmost node of the root splay tree of the auxiliary tree is the root of represented tree.
 */
template <class Monoid>
class link_cut_tree {
    typedef typename Monoid::value_type value_type;
    typedef typename reversible_monoid<Monoid>::value_type reversible_type;
    const reversible_monoid<Monoid> mon;
    std::vector<value_type> data;  // data of the original tree
    std::vector<reversible_type> path;  // sum of data of the sub-tree in the belonging splay tree
    std::vector<int> parent, left, right;  // of the auxiliary tree
    std::vector<bool> is_reversed;  // of the auxiliary tree; not applied to left, right, and path yet

    /**
     * @description returns whether `a` and `parent[a]` is in the same splay tree
     */
    int get_parent_edge_type(int a) const {
        if (parent[a] != -1 and left[parent[a]] == a) {
            assert (not is_reversed[parent[a]]);
            return -1;  // heavy (left-child)
        } else if (parent[a] != -1 and right[parent[a]] == a) {
            assert (not is_reversed[parent[a]]);
            return +1;  // heavy (right-child)
        } else {
            return 0;  // light
        }
    }

    /**
     * @description make `a` the parent of the current parent of `a`
     */
    void rotate(int a) {
        int b = parent[a];
        assert (b != -1);
        assert (not is_reversed[b]);
        assert (not is_reversed[a]);
        switch (get_parent_edge_type(b)) {
            case -1:  // left
                left[parent[b]] = a;
                break;
            case 1:  // right
                right[parent[b]] = a;
                break;
        }
        switch (get_parent_edge_type(a)) {
            case -1:  // left
                parent[a] = std::exchange(parent[b], a);
                left[b] = std::exchange(right[a], b);
                if (left[b] != -1) parent[left[b]] = b;
                break;
            case 1:  // right
                parent[a] = std::exchange(parent[b], a);
                right[b] = std::exchange(left[a], b);
                if (right[b] != -1) parent[right[b]] = b;
                break;
            default:  // root
                assert (false);
        }
        update_path(b);
        update_path(a);
    }

    /**
     * @description make `a` the root of the beloging splay tree
     */
    void splay(int a) {
        propagate_reverse_splay(a);
        while (get_parent_edge_type(a)) {
            // a is not the root of the splay tree
            if (not get_parent_edge_type(parent[a])) {
                // zig step: parent[a] is the root of the splay tree
                rotate(a);
            } else if (get_parent_edge_type(a) == get_parent_edge_type(parent[a])) {
                // zig-zig step
                rotate(parent[a]);
                rotate(a);
            } else {
                // zig-zag step
                rotate(a);
                rotate(a);
            }
        }
    }

    /**
     * @description make `a` the root of the auxiliary tree
     * @note `a` becomes a terminal of the heavy path
     */
    void expose(int a) {
        // make a light path from `a` to the root
        for (int b = a; b != -1; b = parent[b]) {
            splay(b);
        }
        // make `a` the terminal of the path
        assert (not is_reversed[a]);
        left[a] = -1;
        update_path(a);
        // make the path heavy
        for (int b = a; parent[b] != -1; b = parent[b]) {
            left[parent[b]] = b;
            update_path(parent[b]);
        }
        splay(a);
    }

    void propagate_reverse_node(int a) {
        if (is_reversed[a]) {
            is_reversed[a] = false;
            path[a] = reversible_monoid<Monoid>::reverse(path[a]);
            if (right[a] != -1) is_reversed[right[a]] = not is_reversed[right[a]];
            if (left[a] != -1) is_reversed[left[a]] = not is_reversed[left[a]];
            std::swap(left[a], right[a]);
        }
    }
    void propagate_reverse_splay(int a) {
        if (parent[a] != -1 and (left[parent[a]] == a or right[parent[a]] == a)) {
            propagate_reverse_splay(parent[a]);
        }
        propagate_reverse_node(a);
        if (left[a] != -1) propagate_reverse_node(left[a]);
        if (right[a] != -1) propagate_reverse_node(right[a]);
    }

    /**
     * @note `a` should be the root of the splay tree
     */
    void update_path(int a) {
        path[a] = reversible_monoid<Monoid>::make(data[a]);
        if (right[a] != -1) path[a] = mon.mult(path[a], path[right[a]]);
        if (left[a] != -1) path[a] = mon.mult(path[left[a]], path[a]);
    }

public:
    link_cut_tree(int size, const Monoid & mon_ = Monoid())
            : mon(mon_), data(size, mon.base.unit()), path(size, mon.unit()), parent(size, -1), left(size, -1), right(size, -1), is_reversed(size, false) {
    }

    /**
     * @description make a direct edge from `a` to `b`
     * @note `a` must be a root
     * @note `b` must not be a descendant of `a`
     */
    void link(int a, int b) {
        expose(b);  // for the time complexity
        expose(a);  // to make `a` the root
        assert (not is_reversed[a]);
        assert (right[a] == -1);  // `a` must be a root
        parent[a] = b;
    }

    /**
     * @description remove the direct edge from `a`
     * @note `a` must not be a root
     */
    void cut(int a) {
        expose(a);  // to make `a` the root
        assert (not is_reversed[a]);
        assert (right[a] != -1);  // `a` must not be a root
        parent[right[a]] = -1;
        right[a] = -1;
        update_path(a);
    }

    /**
     * @note -1 is returned when `a` and `b` are not in the same tree
     */
    int get_lowest_common_ancestor(int a, int b) {
        expose(b);  // for the time complexity
        expose(a);  // to make `a` the root
        assert (not is_reversed[a]);
        int preserved = -1;
        std::swap(left[a], preserved);  // make `a` and `b` belong different splay trees even if `b` is a descendant of `a`
        int result = b;
        int c = b;
        for (; c != a and c != -1; c = parent[c]) {
            assert (parent[c] != -1);
            if (not get_parent_edge_type(c)) {  // when it enters another splay tree
                result = parent[c];
            }
        }
        std::swap(left[a], preserved);
        return c == a ? result : -1;
    }

    bool are_connected(int a, int b) {
        return get_lowest_common_ancestor(a, b) != -1;
    }

    int get_parent(int a) {
        expose(a);
        assert (not is_reversed[a]);
        if (right[a] == -1) return parent[a];
        for (int b = right[a]; ; b = left[b]) {
            propagate_reverse_node(b);
            if (left[b] == -1) return b;
        }
    }

    int get_root(int a) {
        expose(a);
        assert (not is_reversed[a]);
        while (right[a] != -1) {
            a = right[a];
        }
        return a;
    }

    /**
     * @description make `a` the root of the represented tree
     */
    void evert(int a) {
        expose(a);  // to make `a` the root
        assert (not is_reversed[a]);
        assert (left[a] == -1);  // `a` is the terminal
        is_reversed[a] = true;
    }

    void vertex_set(int a, value_type value) {
        splay(a);  // to make `a` the root of a splay tree
        data[a] = value;
        update_path(a);
    }

    value_type vertex_get(int a) const {
        return data[a];
    }

    value_type path_get(int a, int b) {
        expose(a);  // for the time complexity
        expose(b);  // to make `b` the root
        assert (not is_reversed[a]);
        auto data_a = reversible_monoid<Monoid>::make(data[a]);
        reversible_type up = (right[a] == -1 ? data_a : mon.mult(data_a, path[right[a]]));
        reversible_type down = (left[a] == -1 ? data_a : mon.mult(path[left[a]], data_a));
        for (int c = a; c != b and c != -1; c = parent[c]) {
            assert (parent[c] != -1);
            assert (not is_reversed[parent[c]]);
            auto data_parent_c = reversible_monoid<Monoid>::make(data[parent[c]]);
            switch (get_parent_edge_type(c)) {
                case -1:  // heavy (left-child)
                    up = mon.mult(up, data_parent_c);
                    if (right[parent[c]] != -1) up = mon.mult(up, path[right[parent[c]]]);
                    break;
                case 1:  // heavy (right-child)
                    down = mon.mult(data_parent_c, down);
                    if (left[parent[c]] != -1) down = mon.mult(path[left[parent[c]]], down);
                    break;
                case 0:  // light
                    down = reversible_monoid<Monoid>::reverse(up);
                    up = mon.mult(up, data_parent_c);
                    if (right[parent[c]] != -1) up = mon.mult(up, path[right[parent[c]]]);
                    down = mon.mult(data_parent_c, down);
                    if (left[parent[c]] != -1) down = mon.mult(path[left[parent[c]]], down);
                    break;
            }
        }
        return reversible_monoid<Monoid>::get(reversible_monoid<Monoid>::reverse(down));
    }
};

/**
 * @brief quotient ring / 剰余環 $\mathbb{Z}/n\mathbb{Z}$
 */
template <int32_t MOD>
struct mint {
    int32_t value;
    mint() : value() {}
    mint(int64_t value_) : value(value_ < 0 ? value_ % MOD + MOD : value_ >= MOD ? value_ % MOD : value_) {}
    mint(int32_t value_, std::nullptr_t) : value(value_) {}
    explicit operator bool() const { return value; }
    inline constexpr mint<MOD> operator + (mint<MOD> other) const { return mint<MOD>(*this) += other; }
    inline constexpr mint<MOD> operator - (mint<MOD> other) const { return mint<MOD>(*this) -= other; }
    inline constexpr mint<MOD> operator * (mint<MOD> other) const { return mint<MOD>(*this) *= other; }
    inline constexpr mint<MOD> & operator += (mint<MOD> other) { this->value += other.value; if (this->value >= MOD) this->value -= MOD; return *this; }
    inline constexpr mint<MOD> & operator -= (mint<MOD> other) { this->value -= other.value; if (this->value <    0) this->value += MOD; return *this; }
    inline constexpr mint<MOD> & operator *= (mint<MOD> other) { this->value = (uint_fast64_t)this->value * other.value % MOD; return *this; }
    inline constexpr mint<MOD> operator - () const { return mint<MOD>(this->value ? MOD - this->value : 0, nullptr); }
    inline constexpr bool operator == (mint<MOD> other) const { return value == other.value; }
    inline constexpr bool operator != (mint<MOD> other) const { return value != other.value; }
};
template <int32_t MOD> mint<MOD> operator * (int64_t value, mint<MOD> n) { return mint<MOD>(value) * n; }

template <class CommutativeRing>
struct linear_function_monoid {
    typedef std::pair<CommutativeRing, CommutativeRing> value_type;
    linear_function_monoid() = default;
    value_type unit() const {
        return std::make_pair(1, 0);
    }
    value_type mult(value_type g, value_type f) const {
        CommutativeRing fst = g.first * f.first;
        CommutativeRing snd = g.second + g.first * f.second;
        return std::make_pair(fst, snd);
    }
};

/**
 * @see http://hackage.haskell.org/package/base/docs/Data-Monoid.html#t:Dual
 */
template <class Monoid>
struct dual_monoid {
    typedef typename Monoid::value_type value_type;
    Monoid base;
    value_type unit() const { return base.unit(); }
    value_type mult(const value_type & a, const value_type & b) const { return base.mult(b, a); }
};


constexpr int MOD = 998244353;
int main() {
    int n, q; scanf("%d%d", &n, &q);

    // initialize
    link_cut_tree<dual_monoid<linear_function_monoid<mint<MOD> > > > lct(n);
    REP (i, n) {
        mint<MOD> a_i, b_i; scanf("%d%d", &a_i.value, &b_i.value);
        lct.vertex_set(i, std::make_pair(a_i, b_i));
    }
    std::vector<std::vector<int> > g(n);
    REP (i, n - 1) {
        int u, v; scanf("%d%d", &u, &v);
        g[u].push_back(v);
        g[v].push_back(u);
    }
    std::vector<bool> used(n);
    std::stack<int> stk;
    stk.push(0);
    used[0] = true;
    while (not stk.empty()) {
        int u = stk.top();
        stk.pop();
        for (int v : g[u]) if (not used[v]) {
            lct.link(v, u);
            stk.push(v);
            used[v] = true;
        }
    }

    // answer to queries
    while (q --) {
        int t; scanf("%d", &t);
        if (t == 0) {
            int u, v, w, x; scanf("%d%d%d%d", &u, &v, &w, &x);
            lct.cut(lct.get_parent(u) == v ? u : v);
            lct.evert(w);
            lct.link(w, x);
        } else if (t == 1) {
            int u; mint<MOD> c, d; scanf("%d%d%d", &u, &c.value, &d.value);
            lct.vertex_set(u, std::make_pair(c, d));
        } else if (t == 2) {
            int u, v; mint<MOD> x; scanf("%d%d%d", &u, &v, &x.value);
            auto f = lct.path_get(u, v);
            printf("%d\n", (f.first * x + f.second).value);
        }
    }
    return 0;
}
