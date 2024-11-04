#include "random.h"
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <set>
#include <utility>
#include <vector>

void erdos_renyi(int n, int m, Random &gen) {
  assert(static_cast<long long>(n) * (n - 1) / 2 >= m);

  std::vector<std::pair<int, int>> edges(m);
  if (static_cast<long long>(n) * (n - 1) / 2 > m * 2) {
    // sparse
    std::set<std::pair<int, int>> eset;
    for (auto &e : edges) {
      do {
        e = gen.uniform_pair(0, n - 1);
      } while (!eset.insert(std::minmax(e.first, e.second)).second);
    }
  } else {
    // dense
    std::vector<std::pair<int, int>> all;
    for (int u = 0; u < n; ++u) {
      for (int v = 0; v < u; ++v) {
        if (gen.uniform_bool()) {
          all.emplace_back(u, v);
        } else {
          all.emplace_back(v, u);
        }
      }
    }
    gen.shuffle(all.begin(), all.end());
    std::copy(all.begin(), all.begin() + m, edges.begin());
  }

  std::printf("%d %d\n", n, m);
  for (const auto &e : edges) {
    std::printf("%d %d\n", e.first, e.second);
  }
}
