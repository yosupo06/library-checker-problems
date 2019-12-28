#include "random.h"
#include "../params.h"
#include <iostream>

using namespace std;
using ll = long long;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_AND_Q_MAX;
    int q = N_AND_Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform(-A_ABS_MAX, A_ABS_MAX);
        ll b = gen.uniform(-B_ABS_MAX, B_ABS_MAX);
        printf("%d %lld\n", a, b);
    }
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        printf("%d ", t);
        if (t == 0) {
            int a = gen.uniform(-A_ABS_MAX, A_ABS_MAX);
            ll b = gen.uniform(-B_ABS_MAX, B_ABS_MAX);
            printf("%d %lld\n", a, b);
        } else {
            int p = gen.uniform(-A_ABS_MAX, A_ABS_MAX);
            printf("%d\n", p);
        }
    }
    return 0;
}
