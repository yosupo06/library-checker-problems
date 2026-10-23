#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    Random gen(std::atoll(argv[1]));
    int limit = 0;
    while ((limit + 2LL) * (limit + 3) / 2 <= T_MAX && limit < N_MAX) ++limit;
    std::vector<std::pair<int, int>> queries;
    for (int n = 0; n <= limit; ++n) {
        for (int k = 0; k <= n; ++k) queries.emplace_back(n, k);
    }
    gen.shuffle(queries.begin(), queries.end());
    printf("%d\n", static_cast<int>(queries.size()));
    for (auto q : queries) printf("%d %d\n", q.first, q.second);
}
