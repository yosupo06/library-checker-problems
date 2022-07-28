#include <iostream>
#include <vector>
#include "../params.h"

int main(int, char**) {

    const int n = N_MAX;

    std::vector<std::pair<int, int>> edges;
    for (int i = 1; i < n; ++i) {
        edges.emplace_back(i - 1, i);
    }
    for (int i = 2; i < n; ++i) {
        edges.emplace_back(i - 2, i);
    }

    printf("%d %d\n", n, (int)edges.size());
    for (auto e: edges) {
        printf("%d %d\n", e.first, e.second);
    }
    return 0;
}
