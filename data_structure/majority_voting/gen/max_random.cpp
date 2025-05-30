#include "random.h"
#include <cstdio>

int main(int, char *argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = 500'000;
    int Q = 500'000;
    printf("%d %d\n", N, Q);

    int BLOCK_SIZE = 50'000;
    int BLOCK_NUM = N / BLOCK_SIZE;
    std::vector<int> cands(BLOCK_NUM);
    for (int i = 0; i < BLOCK_NUM; ++i) {
        cands[i] = gen.uniform(0, 1'000'000'000);
    }

    for (int i = 0; i < N; ++i) {
        if (i) {
            printf(" ");
        }
        if (gen.uniform_bool()) {
            printf("%d", cands[i / BLOCK_SIZE]);
        } else if (gen.uniform_bool()) {
            printf("%d", cands[gen.uniform(0, BLOCK_NUM - 1)]);
        } else {
            printf("%d", gen.uniform(0, 1'000'000'000));
        }
    }
    printf("\n");

    for (int i = 0; i < Q; ++i) {
        int t = gen.uniform(0, 1);
        printf("%d ", t);
        if (t == 0) {
            int p = gen.uniform(0, N - 1);
            int x = gen.uniform_bool()
                        ? (gen.uniform_bool()
                               ? cands[p / BLOCK_SIZE]
                               : cands[gen.uniform(0, BLOCK_NUM - 1)])
                        : gen.uniform(0, 1'000'000'000);
            printf("%d %d\n", p, x);
        } else {
            auto [l, r] = gen.uniform_pair(0, N);
            printf("%d %d\n", l, r);
        }
    }

    return 0;
}