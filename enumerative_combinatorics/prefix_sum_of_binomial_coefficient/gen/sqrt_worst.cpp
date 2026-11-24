#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <set>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    Random gen(seed);
    int block = std::max(1, static_cast<int>(N_MAX / std::sqrt(T_MAX)));
    assert(block >= 4 && 2 * block - 1 <= N_MAX);
    printf("%lld\n", T_MAX);
    if (seed == 0) {
        for (int i = 0; i < T_MAX; ++i) {
            printf("%lld %d\n", N_MAX, block / 2 - 1);
        }
        return 0;
    }

    std::set<std::pair<int, int>> used;
    std::vector<std::pair<int, int>> queries;
    while (queries.size() < static_cast<std::size_t>(T_MAX)) {
        int n = queries.empty() ? static_cast<int>(N_MAX) : gen.uniform<int>(2 * block - 1, N_MAX);
        int center = (n + 1) / 2;
        int anchor = gen.uniform(0, center / block - 1) * block;
        int m = gen.uniform_bool() ? anchor + block / 2 : anchor + block - block / 2;
        int k = gen.uniform_bool() ? m - 1 : n - m;
        if (used.emplace(n, k).second) queries.emplace_back(n, k);
    }
    gen.shuffle(queries.begin(), queries.end());
    for (auto [n, k] : queries) printf("%d %d\n", n, k);
}
