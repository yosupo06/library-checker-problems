//complete graph (weights are equal to manhattan distance between uniform random generated points in multidimension space)
#include <iostream>
#include <tuple>
#include "random.h"

using namespace std;

const vector<int> seeds = { 82, 10, 66, 74, 72};

int main(int, char* argv[]) {
    long long seed = atoll(argv[1]);
    if (seed >= 0 && seed < (long long) seeds.size()) {
      seed = seeds[seed];
    } else {
      seed += 100;
    }
    auto gen = Random(seed);
    const int dimensions = 7 + (seed % 2) * 10;
    const int maxw = 1'000'000;
    const int c = maxw / dimensions;
    int n = 500;
    int m = n * (n - 1) / 2;
    using P3 = pair<pair<int, int>, int>;
    vector<vector<int> > p;
    p.reserve(n);
    for (int i = 0; i < n; i++) {
      vector<int> q;
      q.reserve(dimensions);
      for (int j = 0; j < dimensions; ++j) {
        q.push_back(gen.uniform(0, c));
      }
      p.push_back(q);
    }
    vector<P3> edges;
    edges.reserve(m);
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            int w = 0;
            for (int k = 0; k < dimensions; ++k) {
              w += std::abs(p[i][k] - p[j][k]);
            }
            if (w < 1) {
              w = 1;
            }
            if (w > maxw) {
              w = maxw;
            }
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
