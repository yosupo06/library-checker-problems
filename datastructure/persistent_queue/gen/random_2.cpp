#include "random.h"
#include "../params.h"

#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);

    const int q = gen.uniform(Q_MIN, Q_MAX);
    std::printf("%d\n", q);
    std::vector<int> size_(q + 1);
    const auto size = size_.begin() + 1;
    size[-1] = 0;
    for (int i = 0; i != q; i += 1) {
        int c = gen.uniform01() < 0.3 ? 1 : 0;
        const int t = gen.uniform(-1, i - 1);
        if (size[t] == 0) {
            c = 0;
        }
        switch (c) {
            case 0: {
                const int x = gen.uniform(X_MIN, X_MAX);
                std::printf("%d %d %d\n", c, t, x);
                size[i] = size[t] + 1;
            } break;
            case 1: {
                std::printf("%d %d\n", c, t);
                size[i] = size[t] - 1;
            }
        }
    }
}
