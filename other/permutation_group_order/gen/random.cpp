#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char** argv) {
    long long seed = std::atoll(argv[1]);
    Random gen(seed);
    int n = seed < 6 ? gen.uniform(1, 8) : int(N_MAX);
    int k = seed % 3 == 0 ? 1 : (seed % 3 == 1 ? 2 : int(K_MAX));
    std::printf("%d %d\n", n, k);
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    for (int i = 0; i < k; ++i) {
        gen.shuffle(p.begin(), p.end());
        for (int j = 0; j < n; ++j) std::printf("%d%c", p[j], j + 1 == n ? '\n' : ' ');
    }
}
