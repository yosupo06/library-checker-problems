#include "random.h"
#include <iostream>
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(1, N_AND_Q_MAX);
    int q = gen.uniform<int>(1, N_AND_Q_MAX);
    printf("%d %d\n", n, q);
    for (int i = 0; i < n; i++) {
        printf("%d", gen.uniform<int>(0, A_AND_X_MAX));
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int t = gen.uniform(0, 1);
        printf("%d ", t);
        if (t == 0) {
            int p = gen.uniform(0, n - 1);
            int x = gen.uniform<int>(0, A_AND_X_MAX);
            printf("%d %d\n", p, x);
        } else {
            auto p = gen.uniform_pair(0, n);
            printf("%d %d\n", p.first, p.second);
        }
    }
    return 0;
}
