#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MAX;
    int q = Q_MAX;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform(A_MIN, A_MAX);
        printf("%d", a);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int l, r;
        tie(l, r) = gen.uniform_pair(0, n);
        int k = gen.uniform(0, r - l - 1);
        printf("%d %d %d\n", l, r, k);
    }
    return 0;
}
