#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    Random gen(std::atoll(argv[1]));
    int side = 1;
    while ((side + 1LL) * (side + 1) <= T_MAX) ++side;
    std::vector<std::pair<int, int>> queries;
    for (int i = 0; i < side; ++i) {
        int n = static_cast<long long>(i) * N_MAX / (side - 1);
        for (int j = 0; j < side; ++j) {
            int k = static_cast<long long>(j) * n / (side - 1);
            queries.emplace_back(n, k);
        }
    }
    gen.shuffle(queries.begin(), queries.end());
    printf("%d\n", static_cast<int>(queries.size()));
    for (auto q : queries) printf("%d %d\n", q.first, q.second);
}
