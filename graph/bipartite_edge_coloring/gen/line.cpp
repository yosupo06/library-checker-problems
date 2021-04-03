#include <iostream>
#include <set>
#include "random.h"
#include "../params.h"

using namespace std;

int main() {
    int n = min(L_MAX, R_MAX);
    int m = 0;
    using P = pair<int, int>;
    vector<P> edges;
    for (int i = 0; i < n && m < M_MAX; i++) {
        edges.push_back({i, i});
        ++m;
        if (i && m < M_MAX) {
          edges.push_back({i, i - 1});
          ++m;
        }
    }
    printf("%d %d %d\n", n, n, m);
    for (auto edge: edges) {
        printf("%d %d\n", edge.first, edge.second);
    }
    return 0;
}
