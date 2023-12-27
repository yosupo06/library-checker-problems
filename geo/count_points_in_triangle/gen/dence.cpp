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
    int q = Q_MAX;
    printf("%d\n", n);
    for (int i=0; i<n; i++) {
        long long a = gen.uniform(-12, 12);
        long long b = gen.uniform(-12, 12);
        printf("%lld %lld\n", a, b);
    }
    printf("%d\n", m);
    for (int i=0; i<m; i++) {
        long long a = gen.uniform(-9, 9);
        long long b = gen.uniform(-9, 9);
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
