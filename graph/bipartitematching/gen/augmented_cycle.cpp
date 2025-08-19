#include <algorithm>
#include <cassert>
#include <iostream>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    constexpr int L = L_MAX, R = R_MAX, M = M_MAX;
    constexpr int N = std::min(L, R);

    std::vector<std::pair<int, int>> edg;
    if (seed == 0) {
        const int n = std::min(N, M / 3);
        for (int i = 0; i < n; i++) {
            edg.push_back({i, i});
            edg.push_back({i, (i + 1) % n});
            edg.push_back({i, gen.uniform<int>(0, i)});
        }
    } else if (seed == 1) {
        const int n = std::min(N, M / 3);
        const int W = 250;
        for (int i = 0; i < n; i++) {
            edg.push_back({i, i});
            edg.push_back({i, (i + 1) % n});
            edg.push_back({i, gen.uniform<int>(std::max(0, i - 2 * W), std::max(0, i - W))});
        }
    } else if (seed == 2) {
        const int n = std::min(N, M / 3);
        const int W = 1000;
        for (int i = 0; i < n; i++) {
            edg.push_back({i, i});
            edg.push_back({i, (i + 1) % n});
            edg.push_back({i, gen.uniform<int>(std::max(0, i - 2 * W), i)});
        }
    } else {
        assert(false);
    }

    std::sort(edg.begin(), edg.end());
    edg.erase(std::unique(edg.begin(), edg.end()), edg.end());

    std::vector<int> p1(L), p2(R);
    std::iota(p1.begin(), p1.end(), 0);
    std::iota(p2.begin(), p2.end(), 0);

    gen.shuffle(p1.begin(), p1.end());
    gen.shuffle(p2.begin(), p2.end());
    gen.shuffle(edg.begin(), edg.end());

    std::cout << N << " " << N << " " << edg.size() << "\n";
    for (auto& [u, v] : edg) {
        std::cout << p1[u] << " " << p2[v] << "\n";
    }

    return 0;
}
