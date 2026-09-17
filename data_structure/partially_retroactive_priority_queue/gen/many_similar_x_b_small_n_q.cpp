#include <cstdio>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]) ^ 0xf1e6a11c470bd43f;
    auto gen = Random(seed);

    int N = gen.uniform<int>(N_MIN, std::min<int>(N_MAX, 5000));
    int Q = gen.uniform<int>(Q_MIN, std::min<int>(Q_MAX, 5000));
    printf("%d %d\n", N, Q);

    std::vector<int> vals;
    int num_vars = atoll(argv[1]) + 1;
    for (int i = 0; i < num_vars; i++) vals.push_back(gen.uniform<int>(X_MIN, X_MAX));

    auto gen_pair = [&](int t) -> std::pair<int, int> {
        if (t) return {1, -1};
        int x = gen.uniform<int>(X_MIN, X_MAX);
        return {0, x};
    };

    for (int i = 0; i < N; i++) {
        auto [a, b] = gen_pair(i > N * 2 / 3);
        printf("%d %d\n", a, b);
    }

    for (int i = 0; i < Q; i++) {
        int k = gen.uniform<int>(0, N - 1);
        auto [a, b] = gen_pair(i > Q / 2);
        printf("%d %d %d\n", k, a, b);
    }
}
