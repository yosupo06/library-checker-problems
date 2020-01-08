#include "random.h"
#include <cassert>
#include <iostream>
#include <tuple>
#include <vector>
#include "../params.h"
#include "../segtree.hpp"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    assert (0 <= seed and seed < 10);
    int n = seed + 1;  // use the seed, which is an index in the test set, to check n = 2^k - 1, 2^k, 2^k + 1
    int q = 20;
    printf("%d %d\n", n, q);
    vector<typename min_max_monoid::value_type> init(n);
    for (int i = 0; i < n; i++) {
        long long a = gen.uniform<long long>(-A_ABS_MAX, A_ABS_MAX);
        printf("%lld", a);
        if (i != n - 1) printf(" ");
        init[i] = { a, a };
    }
    printf("\n");
    chmin_chmax_add_min_max_segment_tree segtree(init.begin(), init.end());

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 3);
        int l, r;
        tie(l, r) = gen.uniform_pair(0, n);
        if (t == 0) {
            long long b = gen.uniform<long long>(-A_ABS_MAX, A_ABS_MAX);
            printf("%d %d %d %lld\n", t, l, r, b);
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { b, LLONG_MIN, 0ll });
        } else if (t == 1) {
            long long b = gen.uniform<long long>(-A_ABS_MAX, A_ABS_MAX);
            printf("%d %d %d %lld\n", t, l, r, b);
            segtree.range_apply(l, r, (typename chmin_chmax_add_monoid::value_type) { LLONG_MAX, b, 0ll });
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
