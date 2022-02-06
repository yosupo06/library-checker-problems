#include <cstdio>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = std::min<int>(N_MAX, M_MAX + 1);
    int m = n - 1;
    printf("%d %d\n", n, m);

    std::vector<std::pair<int, int>> edges(n-1);
    for(int i=1; i<n; i++){
        int p = gen.uniform<int>(0, i-1);
        edges[i-1] = { i,p };
    }
    
    auto vperm = gen.perm<int>(n);
    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        edges[i] = { vperm[u], vperm[v] };
    }

    for (int i = 0; i < m; i++) {
        auto [u, v] = edges[i];
        printf("%d %d\n", u, v);
    }
    return 0;
}
