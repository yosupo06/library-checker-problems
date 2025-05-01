#include "random.h"
#include <iostream>
#include <tuple>

#include "../params.h"

// hack the splay tree which does not implement the zig-zig (only zig / zig-zag) rotation
// ref: https://judge.yosupo.jp/hack/483
int main(int, char **argv) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    
    int n = 10;
    int q = N_AND_Q_MAX / 2 * 2;
    printf("%d %d\n", n, q);
    
    std::vector<int> a(n);
    for (auto &i : a) i = gen.uniform<int>(0, MOD - 1);
    
    for (int i = 0; i < n; i++) {
        if (i) printf(" ");
        printf("%d", a[i]);
    }
    puts("");
    
    for (int i = 0; i < q / 2; i++) {
        int index;
        if (seed % 2 == 0) {
            index = gen.uniform<int>(0, 9);
        } else {
            index = gen.uniform<int>(i + 0, i + 9);
        }
        printf("0 %d %d\n", index, gen.uniform<int>(0, MOD - 1));
    }

    for (int i = 0; i < q / 2; i++) {
        int l, r;
        if (seed / 2 % 2 == 0) {
            std::tie(l, r) = gen.uniform_pair<int>(0, 9);
        } else {
            std::tie(l, r) = gen.uniform_pair<int>(i + 0, i + 9);
        }
        printf("4 %d %d\n", l, r);
    }
    
    return 0;
}
