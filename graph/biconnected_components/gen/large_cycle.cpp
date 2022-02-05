#include <cstdio>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = std::min(N_MAX, M_MAX);
    int m = n;

    std::vector<std::pair<int, int>> edges;

    int cysize = gen.uniform<int>(n - n/10, n - n/20);
    for(int i=0; i<cysize-1; i++){
        int u = i;
        int v = i+1;
        edges.push_back({ u, v });
    }
    edges.push_back({ 0, cysize-1 });

    for (int i = cysize; i < m; i++) {
        int u = gen.uniform<int>(0, i-1);
        int v = i;
        edges.push_back({ u, v });
    }

    std::vector<int> vtxperm = gen.perm<int>(n);
    for(auto& e : edges){
        e.first = vtxperm[e.first];
        e.second = vtxperm[e.second];
    }

    gen.shuffle(edges.begin(), edges.end());
    
    printf("%d %d\n", n, m);
    for(int i=0; i<m; i++){
        int u = edges[i].first;
        int v = edges[i].second;
        printf("%d %d\n", u, v);
    }
    return 0;
}
