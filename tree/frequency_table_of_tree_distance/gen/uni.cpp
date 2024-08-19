#include <iostream>
#include <tuple>
#include <vector>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int N = N_MAX;

    using edge = std::pair<int, int>;
    std::vector<edge> edges;
    for (int i = 1; i < N; i++) {
        edges.emplace_back(0, i);
    }

    gen.shuffle(edges.begin(), edges.end());
    printf("%d\n", N);
    for (auto e : edges) {
        int u, v;
        std::tie(u, v) = e;
        printf("%d %d\n", u, v);
    }

    return 0;
}
