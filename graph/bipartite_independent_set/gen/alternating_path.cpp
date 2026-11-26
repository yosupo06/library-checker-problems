#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include "../params.h"

int main(int, char** argv) {
    int n = std::min(L_MAX, R_MAX);
    bool perfect = std::atoi(argv[1]) == 0;
    // The last left vertex must displace an entire chain to reach a free right
    // vertex (perfect), or explore the chain and leave one right vertex isolated.
    std::printf("%d %d %d\n", n, n, 2 * n - 2 + int(perfect));
    for (int i = 0; i + 1 < n; ++i) {
        std::printf("%d %d\n", i, i);
        if (i + 2 < n || perfect) std::printf("%d %d\n", i, i + 1);
    }
    std::printf("%d 0\n", n - 1);
}
