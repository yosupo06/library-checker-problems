#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    const int n = min(L_MAX, R_MAX);
    const int c = min(4 + 2 * (n - 2), (int)(M_MAX / 2 * 2));
    using P = pair<int, int>;
    vector<P> edges;
    edges.push_back({0, 0});
    edges.push_back({0, 1});
    edges.push_back({1, 0});
    edges.push_back({1, 1});
    for (int i = 2; i < c / 2; ++i) {
        edges.push_back({i, i - 2});
        edges.push_back({i, i});
    }
    const int m = int(edges.size());
    edges[m - 1].second -= 1;
    gen.shuffle(edges.begin(), edges.end());
    vector<int> left = gen.perm<int>(n);
    vector<int> right = gen.perm<int>(n);

    printf("%d %d %d\n", n, n, m);
    for (auto edge: edges) {
        printf("%d %d\n", left[edge.first], right[edge.second]);
    }
    return 0;
}
