#include "../params.h"
#include "random.h"
#include <algorithm>
#include <cstdio>
#include <utility>

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = std::min(N_MAX, M_MAX + 1);
  int m = n - 1;

  int center = gen.uniform(0, n - 1);

  std::vector<std::pair<int, int>> edges;
  for (int i = 0; i < n; ++i) {
    if (i != center) {
      edges.emplace_back(center, i);
    }
  }

  for (auto &e : edges) {
    if (gen.uniform_bool()) {
      std::swap(e.first, e.second);
    }
  }

  gen.shuffle(edges.begin(), edges.end());

  std::printf("%d %d\n", n, m);
  for (const auto &e : edges) {
    std::printf("%d %d\n", e.first, e.second);
  }
}
