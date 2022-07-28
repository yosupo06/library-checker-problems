#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    int n = 500;
    int m = gen.uniform(1, n * (n - 1) / 2);

    using P3 = pair<pair<int, int>, int>;
    vector<P3> edges;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int w = gen.uniform(1, 1000000);
            if (gen.uniform_bool()) {
                edges.push_back({{i, j}, w});
            } else {
                edges.push_back({{j, i}, w});
            }
        }
    }
    gen.shuffle(edges.begin(), edges.end());
    edges.resize(m);

    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        printf("%d %d %d\n", edges[i].first.first, edges[i].first.second, edges[i].second);
    }
    return 0;
}
