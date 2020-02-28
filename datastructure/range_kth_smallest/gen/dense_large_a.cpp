#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = N_MIN;
    while ((n + 3) * (n + 2) * (n + 1) / 6 <= Q_MAX)
        n += 1;
    int q = (n + 2) * (n + 1) * n / 6;
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        int a = gen.uniform(A_MIN, A_MAX);
        printf("%d", a);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int l = 0; l < n; l += 1) {
        for (int r = l + 1; r <= n; r += 1) {
            for (int k = 0; k < r - l; k += 1) {
                printf("%d %d %d\n", l, r, k);
            }
        }
    }
    return 0;
}
