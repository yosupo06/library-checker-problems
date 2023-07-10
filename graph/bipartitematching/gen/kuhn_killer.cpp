#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;

// https://codeforces.com/blog/entry/58048?#comment-417533
int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = min(L_MAX, R_MAX);
    int k = n / 8 * 2;

    using P = pair<int, int>;
    vector<P> edges;
    for(int i = 0; i < k; i++) {
        edges.emplace_back(i, i);
    }
    for(int i = 0; i < k - 1; i++) {
        edges.emplace_back(i+1, i);
    }
    for(int i = 0; i < k / 2; i++) {
        edges.emplace_back(i, k+2*i);
        edges.emplace_back(2*k+2*i, k+2*i);
        edges.emplace_back(2*k+2*i, 3*k+2*i);
        edges.emplace_back(k+2*i, i);
        edges.emplace_back(k+2*i, 2*k+2*i);
        edges.emplace_back(3*k+2*i, 2*k+2*i);
    }
    for(int j = 0; j < k / 2; j++) {
        int i = k/2-1-j;
        edges.emplace_back(k/2+j, k+2*i+1);
        edges.emplace_back(2*k+2*i+1, k+2*i+1);
        edges.emplace_back(2*k+2*i+1, 3*k+2*i+1);
        edges.emplace_back(k+2*i+1, k/2+j);
        edges.emplace_back(k+2*i+1, 2*k+2*i+1);
        edges.emplace_back(3*k+2*i+1, 2*k+2*i+1);
    }
    
    int m = int(edges.size());
    gen.shuffle(edges.begin(), edges.end());

    printf("%d %d %d\n", n, n, m);
    for (auto edge: edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}