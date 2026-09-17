#include <cstdio>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]) ^ 0x92013fadc7c03004;
    auto gen = Random(seed);

    int N, Q;
    if (atoll(argv[1])) {
        N = gen.uniform<int>(std::max<int>(N_MIN, N_MAX - 1000), N_MAX);
        Q = gen.uniform<int>(std::max<int>(Q_MIN, Q_MAX - 1000), Q_MAX);
    } else {
        N = gen.uniform<int>(N_MIN, std::min<int>(N_MAX, 5000));
        Q = gen.uniform<int>(Q_MIN, std::min<int>(Q_MAX, 5000));
    }
    printf("%d %d\n", N, Q);

    auto gen_pair = [&]() -> std::pair<int, int> {
        double d = gen.uniform01();
        if (d < .1) return {2, -1};
        if (d < .4) return {1, -1};
        int x = gen.uniform<int>(X_MIN, X_MAX);
        return {0, x};
    };

    for (int i = 0; i < N; i++) {
        printf("%d %d\n", 2, -1);
    }

    for (int i = 0; i < Q; i++) {
        int k = gen.uniform<int>(0, N - 1);
        auto [a, b] = gen_pair();
        printf("%d %d %d\n", k, a, b);
    }
}
