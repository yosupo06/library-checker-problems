#include "../params.h"
#include "network.h"

int main(int, char* argv[]) {
    const int seed = std::atoi(argv[1]);
    Random rng(seed);
    const int n = N_MAX;
    Network g(n, 0, n - 1);
    auto ids = rng.perm<int>(n * n);
    for (int i = 0; i < M_MAX; ++i) {
        const long long c = seed == 0 ? 1 : (seed == 1 ? C_MAX : mixed_capacity(rng, C_MAX));
        g.add(ids[i] / n, ids[i] % n, c);
    }
    g.permute_vertices(rng);
    g.print(N_MAX, M_MAX, C_MAX);
}
