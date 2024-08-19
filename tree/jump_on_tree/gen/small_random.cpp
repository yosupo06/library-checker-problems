#include <iostream>
#include <tuple>
#include <vector>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform(1, 100);
  int Q = Q_MAX;
  std::vector<int> par(N, -1);
  for (int i = 1; i < N; i++) { par[i] = gen.uniform(0, i - 1); }

  using edge = std::pair<int, int>;
  std::vector<edge> edges;
  for (int i = 1; i < N; i++) { edges.emplace_back(i, par[i]); }

  gen.shuffle(edges.begin(), edges.end());
  printf("%d %d\n", N, Q);
  for (auto e: edges) {
    int u, v;
    std::tie(u, v) = e;
    printf("%d %d\n", u, v);
  }
  for (int q = 0; q < Q; ++q) {
    int s, t, i;
    s = gen.uniform<int>(0, N - 1);
    t = gen.uniform<int>(0, N - 1);
    i = gen.uniform<int>(0, N - 1);
    printf("%d %d %d\n", s, t, i);
  }

  return 0;
}
