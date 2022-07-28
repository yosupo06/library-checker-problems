#include <cstdio>
#include <vector>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = std::min(N_MAX, M_MAX / 2);
    int m = M_MAX;
    int cent = n/2;
    printf("%d %d\n", n, m);

    // line
    std::vector<std::pair<int, int>> edges;
    for(int i=1; i<n; i++){
        edges.push_back({ i, i-1 });
    }
    
    // clique
    for(int r=cent; (int)edges.size()<m; r++)
        for(int l=cent; l<r-1 && (int)edges.size()<m; l++)
            edges.push_back({ l, r });
    
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
