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

    int d1 = -1, d2 = -1;
    if (seed == 0) {
        d1 = 2, d2 = 1;
    } else if (seed == 1) {
        d1 = 2, d2 = 2;
    } else if (seed == 2) {
        d1 = 2, d2 = 3;
    } else if (seed == 3) {
        d1 = 3, d2 = 3;
    } else if (seed == 4) {
        d1 = 4, d2 = 8;
    } else {
        assert(false);
    }
    assert(d1 > 0 && d2 > 0);

    int n = 0;
    std::vector<std::pair<int, int>> edg;
    for (int i = 0; i < N && edg.size() < M; i++) {
        n++;
        for (int j = std::max(0, i - d1 + 1); j <= i && edg.size() < M; j++) {
            edg.push_back({i, j});
        }
        for (int j = 0; j < d2 && edg.size() < M; j++) {
            edg.push_back({i, gen.uniform<int>(0, i)});
        }
        if (edg.size() >= M) {
            std::sort(edg.begin(), edg.end());
            edg.erase(std::unique(edg.begin(), edg.end()), edg.end());
        }
    }

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
