#include <bits/stdc++.h>
#include "random.h"

using namespace std;

int main(int argc, char* argv[]) {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);
    cout << fixed << setprecision(20);

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int l = gen.uniform(1, 100'000);
    int r = gen.uniform(1, 100'000);
    int m = gen.uniform(1, 200'000);

    using P = pair<int, int>;
    set<P> edges;
    for (int ph = 0; ph < m; ph++) {
        int u = gen.uniform(0, l - 1);
        int v = gen.uniform(0, r - 1);
        edges.insert({u, v});
    }
    m = int(edges.size());

    cout << l << " " << r << " " << m << endl;
    for (auto edge: edges) {
        cout << edge.first << " " << edge.second << endl;
    }
    return 0;
}