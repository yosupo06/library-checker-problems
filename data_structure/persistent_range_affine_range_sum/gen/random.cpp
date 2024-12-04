#include "random.h"
#include <cstdio>
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(N_MIN, N_MAX);
    int q = gen.uniform<int>(Q_MIN, Q_MAX);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform<int>(0, MOD - 1);
        printf("%d", a);
        if (i != n - 1) printf(" ");
    }
    printf("\n");

    std::vector<int> data_enable;
    data_enable.push_back(-1);
    auto choose_data = [&]() -> int {
        int i = gen.uniform(0, (int)data_enable.size() - 1);
        return data_enable[i];
    };

    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 2);
        int k = choose_data();
        printf("%d %d ", t, k);
        if (t == 0) {
            int l, r;
            tie(l, r) = gen.uniform_pair(0, n);
            int b = gen.uniform<int>(1, MOD - 1);
            int c = gen.uniform<int>(0, MOD - 1);
            printf("%d %d %d %d\n", l, r, b, c);
        } else if(t == 1) {
            int s = choose_data();
            auto [l,r] = gen.uniform_pair(0, n);
            printf("%d %d %d\n", s, l, r);
        } else {
            auto [l,r] = gen.uniform_pair(0, n);
            printf("%d %d\n", l, r);
        }
    }
    return 0;
}
