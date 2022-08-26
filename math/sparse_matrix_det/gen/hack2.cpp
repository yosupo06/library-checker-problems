#include <iostream>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char *argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = min(N_MAX, M_MAX/3);
    int k = n * 3 - 2;
    vector<int> a(k);
    vector<int> b(k);
    vector<int> c(k);
    for (int i = 1; i < n; i++) {
        a[i*3-2] = i; b[i*3-2] = 0;
        a[i*3-1] = i; b[i*3-1] = i;
        a[i*3-0] = 0; b[i*3-0] = i;
    }
    for (int i = 0; i < k; i++) {
        c[i] = gen.uniform<int>(1, MOD - 1);
    }

    printf("%d %d\n", n, k);
    for (int i = 0; i < k; i++) {
        printf("%d %d %d\n", a[i], b[i], c[i]);
    }
    return 0;
}
