#include <cstdio>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = gen.uniform(static_cast<int>(N_MAX - 10), static_cast<int>(N_MAX));
    int m = gen.uniform(2, static_cast<int>(M_MAX));
    std::printf("%d %d\n", n, m);
    std::vector<std::vector<int>> a(n, std::vector<int>(n));
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            a[i][j] = gen.uniform(0, m - 1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::printf("%d", a[i][j]);
            if (j + 1 != n) std::printf(" ");
        }
        std::printf("\n");
    }
    return 0;
}
