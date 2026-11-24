#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
    Random gen(std::atoll(argv[1]));
    std::vector<std::pair<int, int>> queries;
    for (int i = 0; i < T_MAX; ++i) {
        int n = 1 + static_cast<long long>(i) * (N_MAX - 1) / (T_MAX - 1);
        int high = std::max(0, (n - 3) / 2);
        int low = std::max(0, high - n / 8);
        int k = gen.uniform(low, high);
        if (i == T_MAX - 1) k = high;
        queries.emplace_back(n, k);
    }
    gen.shuffle(queries.begin(), queries.end());
    printf("%d\n", static_cast<int>(queries.size()));
    for (auto q : queries) printf("%d %d\n", q.first, q.second);
}
