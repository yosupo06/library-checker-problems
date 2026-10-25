#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    Random gen(seed);
    int block = std::max(1, static_cast<int>(N_MAX / std::sqrt(T_MAX)));
    bool transpose = seed & 1;
    int limit = transpose ? (N_MAX - 1) / 2 : N_MAX;
    int blocks = limit / block + 1;
    std::vector<std::pair<int, int>> queries;
    for (int b = 0; b < blocks; ++b) {
        int low = b * block;
        int high = std::min(limit, low + block - 1);
        if (!transpose) low = std::max(1, low);
        int count = T_MAX / blocks + (b < T_MAX % blocks);
        for (int j = 0; j < count; ++j) {
            int n, k;
            if (!transpose) {
                n = (j & 1) ? high : low;
                k = static_cast<long long>(j) * ((low - 1) / 2) / (count - 1);
            } else {
                k = (j & 1) ? high : low;
                int min_n = 2 * high + 1;
                n = min_n + static_cast<long long>(j) * (N_MAX - min_n) / (count - 1);
            }
            queries.emplace_back(n, k);
        }
    }
    gen.shuffle(queries.begin(), queries.end());
    printf("%d\n", static_cast<int>(queries.size()));
    for (auto q : queries) printf("%d %d\n", q.first, q.second);
}
