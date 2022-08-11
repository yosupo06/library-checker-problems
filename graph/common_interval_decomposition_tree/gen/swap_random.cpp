#include "../params.h"
#include "random.h"

#include <algorithm>
#include <array>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <utility>
#include <vector>

int main(int, char* argv[])
{
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);
    const int n = gen.uniform(N_MIN, N_MAX);
    std::vector<int> p(n);
    std::iota(p.begin(), p.end(), 0);
    if (gen.uniform_bool())
        std::reverse(p.begin(), p.end());
    int q = gen.uniform(0, n);
    while (q--) {
        auto [s, t] = gen.uniform_pair<int>(P_MIN, n - 1);
        std::swap(p[s], p[t]);
    }
    printf("%d\n", n);
    for (int i = 0; i < n; ++i) {
        if (i)
            printf(" ");
        printf("%d", p[i]);
    }
    printf("\n");
}
