#include "../params.h"
#include "random.h"

#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <vector>

int main(int, char* argv[])
{
    long long seed = std::atoll(argv[1]);
    auto gen = Random(seed);
    const int n = N_MAX;
    std::vector<int> p(n);
    auto dfs = [&](auto dfs, int l, int r, int mn, int mx, bool rev) -> void {
        if (r - l < 5) {
            auto tmp = gen.perm<int>(r - l);
            for (int i = 0; i < r - l; ++i)
                p[l + i] = tmp[i] + mn;
        } else {
            int m = (l + r) / 2;
            if (rev) {
                dfs(dfs, l, m, mn + (r - m), mx, 0);
                dfs(dfs, m, r, mn, mn + (r - m), 0);
            } else {
                dfs(dfs, l, m, mn, mn + (m - l), 1);
                dfs(dfs, m, r, mn + (m - l), mx, 1);
            }
        }
    };
    dfs(dfs, 0, n, 0, n, 0);
    std::cout << n << '\n';
    for (int i = 0; i < n; ++i) {
        if (i)
            std::cout << " ";
        std::cout << p[i];
    }
    std::cout << '\n';
}
