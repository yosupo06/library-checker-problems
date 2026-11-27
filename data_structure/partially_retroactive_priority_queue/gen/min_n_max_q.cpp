#include <cstdio>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]) ^ 0x5604297d786132bd;
    auto gen = Random(seed);

    int N = N_MIN;
    int Q = Q_MAX;
    printf("%d %d\n", N, Q);

    auto gen_pair = [&]() -> std::pair<int, int> {
        double d = gen.uniform01();
        if (d < .4) return {1, -1};
        int x = gen.uniform<int>(X_MIN, X_MAX);
        return {0, x};
    };

    for (int i = 0; i < N; i++) {
        auto [t, x] = gen_pair();
        printf("%d %d\n", t, x);
    }

    for (int i = 0; i < Q; i++) {
        int k = gen.uniform<int>(0, N - 1);
        auto [a, b] = gen_pair();
        printf("%d %d %d\n", k, a, b);
    }
}
