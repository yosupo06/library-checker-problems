#include <cstdio>
#include <vector>
#include <algorithm>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]) ^ 0xf48c3e19b5c0ae8c;
    auto gen = Random(seed);

    int log_n;
    {
        int log_n_max = 1, log = 0;
        while (log_n_max * 2 <= N_MAX) log_n_max *= 2, log++;
        log_n = gen.uniform<int>(0, log);
    }
    int N = 1 << log_n;
    int Q = gen.uniform<int>(Q_MIN, Q_MAX);
    printf("%d %d\n", N, Q);

    std::vector<int> k_pos;
    for (int i = 0; i <= log_n; i++) {
        int j = 1 << i;
        for (int k = j - 2; k <= j + 2; k++) if (0 <= k && k < N) k_pos.push_back(k);
    }
    int K = k_pos.size();
    std::sort(k_pos.begin(), k_pos.end());
    k_pos.erase(std::unique(k_pos.begin(), k_pos.end()), k_pos.end());
    std::vector<int> valid_pos(N);
    for (int k : k_pos) valid_pos[k] = 1;

    auto gen_pair = [&]() -> std::pair<int, int> {
        double d = gen.uniform01();
        if (d < .4) return {1, -1};
        int x = gen.uniform<int>(X_MIN, X_MAX);
        return {0, x};
    };

    for (int i = 0; i < N; i++) {
        if (valid_pos[i]) {
            auto [t, x] = gen_pair();
            printf("%d %d\n", t, x);
        } else {
            printf("%d %d\n", 2, -1);
        }
    }

    for (int i = 0; i < Q; i++) {
        int k = k_pos[gen.uniform<int>(0, K - 1)];
        auto [a, b] = gen_pair();
        printf("%d %d %d\n", k, a, b);
    }
}
