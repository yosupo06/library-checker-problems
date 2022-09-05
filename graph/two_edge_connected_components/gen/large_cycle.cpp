#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(N_MAX/2, N_MAX);
    int m = n;
    auto P = gen.perm<int>(n);
    printf("%d %d\n", n, m);
    for (int i = 0; i < n; i++) {
        int a = P[i];
        int b = P[(i + 1) % n];
        printf("%d %d\n", a, b);
    }
    return 0;
}
