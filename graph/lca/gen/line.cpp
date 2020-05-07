#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform<int>(N_MIN, N_MAX);
    int q = gen.uniform<int>(Q_MIN, Q_MAX);
    printf("%d %d\n", n, q);
    for (int i = 1; i < n; i++) {
        printf("%d", i - 1);
        if (i != n - 1) printf(" ");
    }
    printf("\n");
    for (int i = 0; i < q; i++) {
        int u, v;
        std::tie(u, v) = gen.uniform_pair<int>(0, n - 1);
        printf("%d %d\n", u, v);
    }
    return 0;
}
