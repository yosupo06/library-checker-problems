#include "random.h"
#include "../params.h"

#include <cstdio>
#include <cstdlib>

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);

    const int q = Q_MAX;
    std::printf("%d\n", q);
    const int h = q / 2;
    for (int i = 0; i != h; i += 1) {
        const int c = 0;
        const int t = i - 1;
        const int x = gen.uniform(X_MIN, X_MAX);
        std::printf("%d %d %d\n", c, t, x);
    }
    for (int i = h; i != q; i += 1) {
        switch ((i - h) % 3) {
            case 0: {
                const int c = 0;
                const int t = h - 1;
                const int x = gen.uniform(X_MIN, X_MAX);
                std::printf("%d %d %d\n", c, t, x);
            } break;
            case 1: {
                const int c = 1;
                const int t = i - 1;
                std::printf("%d %d\n", c, t);
            } break;
            case 2: {
                const int c = 1;
                const int t = i - 1;
                std::printf("%d %d\n", c, t);
            } break;
        }
    }
}
