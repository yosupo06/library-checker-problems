#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    int m = M_MAX;
    int q = min<long long>(Q_MAX, 4000'0000 / m);
    printf("%d\n", n);
    for (int i=0; i<n; i++) {
        long long a = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        long long b = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        printf("%lld %lld\n", a, b);
    }
    printf("%d\n", m);
    for (int i=0; i<m; i++) {
        long long a = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        long long b = gen.uniform(-X_AND_Y_ABS_MAX, X_AND_Y_ABS_MAX);
        printf("%lld %lld\n", a, b);
    }
    printf("%d\n", q);
    for (int i=0; i<q; i++) {
        int a = gen.uniform(0, n-1);
        int b = gen.uniform(0, n-1);
        int c = gen.uniform(0, n-1);
        printf("%d %d %d\n", a, b, c);
    }
    return 0;
}
