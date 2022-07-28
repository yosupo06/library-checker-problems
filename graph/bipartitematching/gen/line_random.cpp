#include <iostream>
#include <set>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = min(L_MAX, R_MAX);

    using P = pair<int, int>;
    vector<P> edges;
    for (int i = 0; i < n; i++) {
        edges.push_back({i, i});
        if (i) edges.push_back({i, i - 1});
    }
    int m = int(edges.size());
    gen.shuffle(edges.begin(), edges.end());
    vector<int> left = gen.perm<int>(n);
    vector<int> right = gen.perm<int>(n);

    printf("%d %d %d\n", n, n, m);
    for (auto edge: edges) {
        printf("%d %d\n", left[edge.first], right[edge.second]);
    }
    return 0;
}
