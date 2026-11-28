#include <numeric>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include "../params.h"
#include "random.h"

int main(int, char** argv) {
    int seed = std::atoi(argv[1]);
    Random rng(seed);
    int l = L_MAX, r = R_MAX, m = M_MAX;
    if (seed == 0) {
        l = 37;
        r = 29;
        m = 100;
    } else if (seed == 1) {
        l = 400;
        r = 500;
    } else if (seed == 2) {
        l = 7;
    }
    long long pairs = 1LL * l * r;
    std::vector<long long> edges;
    if (m == pairs) {
        edges.resize(m);
        std::iota(edges.begin(), edges.end(), 0LL);
    } else {
        edges = rng.choice(m, 0LL, pairs - 1);
    }
    rng.shuffle(edges.begin(), edges.end());
    std::printf("%d %d %d\n", l, r, m);
    for (long long id : edges) std::printf("%d %d\n", int(id / r), int(id % r));
}
