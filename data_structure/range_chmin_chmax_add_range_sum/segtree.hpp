#pragma once
#include <algorithm>
#include <cassert>
#include <climits>
#include <utility>
#include <vector>

template <class MonoidX, class MonoidF, class Action>
struct lazy_propagation_segment_tree {
    typedef typename MonoidX::value_type value_type;
    typedef typename MonoidF::value_type operator_type;
    const MonoidX mon_x;
    const MonoidF mon_f;
    const Action act;
    int n;
    std::vector<value_type> a;
    std::vector<operator_type> f;

    lazy_propagation_segment_tree() = default;
    lazy_propagation_segment_tree(int n_, const MonoidX & mon_x_ = MonoidX(), const MonoidF & mon_f_ = MonoidF(), const Action & act_ = Action())
            : mon_x(mon_x_), mon_f(mon_f_), act(act_) {
        n = 1; while (n < n_) n *= 2;
        a.resize(2 * n - 1, mon_x.unit());
        f.resize(n - 1, mon_f.unit());
    }
    template <class InputIterator>
    lazy_propagation_segment_tree(InputIterator first, InputIterator last, const MonoidX & mon_x_ = MonoidX(), const MonoidF & mon_f_ = MonoidF(), const Action & act_ = Action())
            : mon_x(mon_x_), mon_f(mon_f_), act(act_) {
        int size = std::distance(first, last);
        n = 1; while (n < size) n *= 2;
        a.resize(2 * n - 1, mon_x.unit());
        f.resize(n - 1, mon_f.unit());
        std::copy(first, last, a.begin() + (n - 1));
        for (int i = n - 2; i >= 0; -- i) {
            a[i] = mon_x.mult(a[2 * i + 1], a[2 * i + 2]);
        }
    }

    void range_apply(int l, int r, operator_type g) {
        assert (0 <= l and l <= r and r <= n);
        range_apply(0, 0, n, l, r, g);
    }
    void range_apply(int i, int il, int ir, int l, int r, operator_type g) {
        if (l <= il and ir <= r) { // 0-based
            a[i] = act(g, a[i]);
            if (i < (int)f.size()) f[i] = mon_f.mult(g, f[i]);
        } else if (ir <= l or r <= il) {
            // nop
        } else {
            range_apply(2 * i + 1, il, (il + ir) / 2, 0, n, f[i]);
            range_apply(2 * i + 2, (il + ir) / 2, ir, 0, n, f[i]);
            f[i] = mon_f.unit();  // unnecessary if the oprator monoid is commutative
            range_apply(2 * i + 1, il, (il + ir) / 2, l, r, g);
            range_apply(2 * i + 2, (il + ir) / 2, ir, l, r, g);
            a[i] = mon_x.mult(a[2 * i + 1], a[2 * i + 2]);
        }
    }

    value_type range_get(int l, int r) {
        assert (0 <= l and l <= r and r <= n);
        if (l == 0 and r == n) return a[0];
        value_type lacc = mon_x.unit(), racc = mon_x.unit();
        for (int l1 = (l += n), r1 = (r += n) - 1; l1 > 1; l /= 2, r /= 2, l1 /= 2, r1 /= 2) {  // 1-based loop, 2x faster than recursion
            if (l < r) {
                if (l % 2 == 1) lacc = mon_x.mult(lacc, a[(l ++) - 1]);
                if (r % 2 == 1) racc = mon_x.mult(a[(-- r) - 1], racc);
            }
            lacc = act(f[l1 / 2 - 1], lacc);
            racc = act(f[r1 / 2 - 1], racc);
        }
        return mon_x.mult(lacc, racc);
    }
};

struct min_max_monoid {
    struct value_type {
        long long min;
        long long max;
    };
    value_type unit() const {
        return (value_type) { LLONG_MAX, LLONG_MIN };
    }
    value_type mult(value_type a, value_type b) const {
        return (value_type) { std::min(a.min, b.min), std::max(a.max, b.max) };
    }
};

struct chmin_chmax_add_monoid {
    // lambda x: min(a, max(b, c + x))
    struct value_type {
        long long chmin;
        long long chmax;
        long long add;
    };
    value_type unit() const {
        return (value_type) { LLONG_MAX, LLONG_MIN, 0ll };
    }
    value_type mult(value_type a, value_type b) const {
        value_type c = b;
        // add
        if (c.chmin != LLONG_MAX) {
            c.chmin += a.add;
        }
        if (c.chmax != LLONG_MIN) {
            c.chmax += a.add;
        }
        c.add += a.add;
        // chmax
        c.chmin = std::max(a.chmax, c.chmin);
        c.chmax = std::max(a.chmax, c.chmax);
        // chmin
        c.chmin = std::min(a.chmin, c.chmin);
        return c;
    }
};

struct chmin_chmax_add_min_max_action {
    typedef typename chmin_chmax_add_monoid::value_type F;
    typedef typename min_max_monoid::value_type X;
    X operator () (F f, X x) const {
        if (x.min == LLONG_MAX) {
            assert (x.max == LLONG_MIN);
            return x;
        }
        X y;
        y.min = std::min(f.chmin, std::max(f.chmax, f.add + x.min));
        y.max = std::min(f.chmin, std::max(f.chmax, f.add + x.max));
        return y;
    }
};

typedef lazy_propagation_segment_tree<min_max_monoid, chmin_chmax_add_monoid, chmin_chmax_add_min_max_action> chmin_chmax_add_min_max_segment_tree;
