#include <cstdio>
#include <cstdlib>
#include <utility>
#include <vector>
#include "../params.h"
#include "random.h"

int main(int, char** argv) {
    int seed = std::atoi(argv[1]);
    Random rng(seed);
    int n = std::min(L_MAX, R_MAX);
    auto left = rng.perm<int>(n);
    auto right = rng.perm<int>(n);
    std::vector<std::pair<int, int>> edges;
    // Each pair of stars forces the optimum to use leaves from both sides.
    // Vertices beyond the last block are isolated.
    int block = seed == 0 ? 3 : 97;
    for (int base = 0; base + block <= n; base += block) {
        for (int i = 1; i < block; ++i) {
            edges.emplace_back(left[base], right[base + i]);
            edges.emplace_back(left[base + i], right[base]);
        }
    }
    rng.shuffle(edges.begin(), edges.end());
    std::printf("%d %d %d\n", n, n, int(edges.size()));
    for (auto [a, b] : edges) std::printf("%d %d\n", a, b);
}
