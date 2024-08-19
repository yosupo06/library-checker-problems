#ifndef INCLUDE_GEN_TREE
#define INCLUDE_GEN_TREE

#include <utility>
#include <vector>

#include "random.h"

std::vector<std::pair<int, int>> random_edges(int n, Random& gen) {
    std::vector<std::pair<int, int>> edges;
    const auto perm = gen.perm<int>(n);
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(perm[gen.uniform(0, i - 1)], perm[i]);
    }
    return edges;
}

std::vector<std::pair<int, int>> binary_tree_edges(int n, Random& gen) {
    const auto perm = gen.perm<int>(n);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n; ++i) {
        int l = 2 * i + 1;
        if (l < n) edges.emplace_back(perm[i], perm[l]);
        int r = 2 * i + 2;
        if (r < n) edges.emplace_back(perm[i], perm[r]);
    }
    return edges;
}

std::vector<std::pair<int, int>> line_edges(int n, Random& gen) {
    const auto perm = gen.perm<int>(n);
    std::vector<std::pair<int, int>> edges;
    for (int i = 0; i < n - 1; ++i) {
        edges.emplace_back(perm[i], perm[i + 1]);
    }
    return edges;
}

std::vector<std::pair<int, int>> uni_edges(int n, Random& gen) {
    std::vector<std::pair<int, int>> edges;
    const auto perm = gen.perm<int>(n);
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(perm[0], perm[i]);
    }
    return edges;
}

#endif // INCLUDE_GEN_TREE