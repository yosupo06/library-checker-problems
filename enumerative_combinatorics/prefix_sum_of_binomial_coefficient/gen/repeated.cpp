#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    long long seed = std::atoll(argv[1]);
    Random gen(seed);
    std::vector<std::pair<int, int>> queries;
    for (int i = 0; i < T_MAX; ++i) {
        int n, k;
        if (seed == 0) {
            n = N_MAX;
            k = static_cast<long long>(i) * N_MAX / (T_MAX - 1);
        } else {
            k = N_MAX / 3;
            n = gen.uniform<int>(k, N_MAX);
        }
        queries.emplace_back(n, k);
    }
    gen.shuffle(queries.begin(), queries.end());
    printf("%d\n", static_cast<int>(queries.size()));
    for (auto q : queries) printf("%d %d\n", q.first, q.second);
}
