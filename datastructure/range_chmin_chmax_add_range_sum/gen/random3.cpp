#include "random.h"
#include <iostream>
#include <tuple>
#include <vector>
#include "../params.h"
#include "../segtree.hpp"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    vector<typename min_max_monoid::value_type> init(n);

    long long mx = A_ABS_MAX;
    long long ma = mx / q;
    long long mn = A_ABS_MAX;
    long long mb = mn / q;
    for (int i = 0; i < n; i++) {
        long long a = i & 1 ? mx : -mn;
        printf("%lld", a);
        if (i != n - 1) printf(" ");
        init[i] = { a, a };
    }
    printf("\n");
    chmin_chmax_add_min_max_segment_tree segtree(init.begin(), init.end());

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        if (i == q - 1) t = 3;
        int l, r;
        tie(l, r) = gen.uniform_pair(0, n);
        if (t == 0) {
            mx = gen.uniform<long long>(mx - ma, mx - 1);
            printf("%d %d %d %lld\n", t, l, r, mx);
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { mx, LLONG_MIN, 0ll });
        } else if (t == 1) {
            mn = gen.uniform<long long>(mn - mb, mn - 1);
            printf("%d %d %d %lld\n", t, l, r, -mn);
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { LLONG_MAX, -mn, 0ll });
        } else if (t == 2) {
            auto c = segtree.range_get(0, n);
            long long b = gen.uniform<long long>(-A_ABS_MAX - c.min, A_ABS_MAX - c.max);
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { LLONG_MAX, LLONG_MIN, b });
            printf("%d %d %d %lld\n", t, l, r, b);
        } else {
            printf("%d %d %d\n", t, l, r);
        }
    }
    return 0;
}
