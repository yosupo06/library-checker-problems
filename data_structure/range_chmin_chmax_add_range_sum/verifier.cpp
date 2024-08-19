#include <vector>
#include "testlib.h"
#include "params.h"
#include "segtree.hpp"

int main() {
    registerValidation();

    int n = inf.readInt(1, N_AND_Q_MAX, "N");
    inf.readSpace();
    int q = inf.readInt(1, N_AND_Q_MAX, "Q");
    inf.readChar('\n');

    std::vector<typename min_max_monoid::value_type> init(n);
    for (int i = 0; i < n; i++) {
        long long a = inf.readLong(-A_ABS_MAX, A_ABS_MAX, "a_i");
        if (i != n - 1) inf.readSpace();
        init[i] = { a, a };
    }
    inf.readChar('\n');
    chmin_chmax_add_min_max_segment_tree segtree(init.begin(), init.end());

    for (int i = 0; i < q; i++) {
        int t = inf.readInt(0, 3, "t");
        inf.readSpace();
        int l = inf.readInt(0, n - 1, "l");
        inf.readSpace();
        int r = inf.readInt(l + 1, n, "r");
        if (t == 0) {
            inf.readSpace();
            long long b = inf.readLong(-2*A_ABS_MAX, 2*A_ABS_MAX, "b");
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { b, LLONG_MIN, 0ll });
        } else if (t == 1) {
            inf.readSpace();
            long long b = inf.readLong(-2*A_ABS_MAX, 2*A_ABS_MAX, "b");
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { LLONG_MAX, b, 0ll });
        } else if (t == 2) {
            inf.readSpace();
            long long b = inf.readLong(-2*A_ABS_MAX, 2*A_ABS_MAX, "b");
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { LLONG_MAX, LLONG_MIN, b });
        } else {
            // nop
        }
        auto a = segtree.range_get(0, n);
        ensure(-A_ABS_MAX <= a.min);
        ensure(a.max <= A_ABS_MAX);
        inf.readChar('\n');
    }
    inf.readEof();
    return 0;
}
