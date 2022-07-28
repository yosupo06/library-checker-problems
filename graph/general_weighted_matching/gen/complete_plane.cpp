//complete graph (weights are equal to distance between uniform random generated points in the square)
#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    auto gen = Random(seed);
    int n = 500;
    int m = n * (n - 1) / 2;
    using P3 = pair<pair<int, int>, int>;
    vector<pair<int, int>> p;
    p.reserve(n);
    for (int i = 0; i < n; i++) {
      p.emplace_back(gen.uniform(0, 707106), gen.uniform(0, 707106));
    }
    vector<P3> edges;
    edges.reserve(m);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int w = (int) (0.5 + hypot(p[i].first - p[j].first, p[i].second - p[j].second));
            if (w < 1) { w = 1; }
            if (gen.uniform_bool()) {
                edges.push_back({{i, j}, w});
            } else {
                edges.push_back({{j, i}, w});
            }
        }
    }
    gen.shuffle(edges.begin(), edges.end());
    printf("%d %d\n", n, m);
    for (int i = 0; i < m; i++) {
        printf("%d %d %d\n", edges[i].first.first, edges[i].first.second, edges[i].second);
    }
    return 0;
}
