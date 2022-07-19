#include <iostream>
#include <tuple>
#include <vector>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int Q = Q_MAX;

  using edge = std::pair<int, int>;
  std::vector<edge> edges;
  for (int i = 1; i < N; i++) { edges.emplace_back(0, i); }

  gen.shuffle(edges.begin(), edges.end());
  printf("%d %d\n", N, Q);
  for (auto e: edges) {
    int u, v;
    std::tie(u, v) = e;
    printf("%d %d\n", u, v);
  }

  for (int q = 0; q < Q; ++q) {
    int s = gen.uniform<int>(0, N - 1);
    int t = gen.uniform<int>(0, N - 1);
    int dst = 2;
    int i;
    if (gen.uniform<int>(0, 9) == 0) {
      i = gen.uniform<int>(0, N - 1);
    } else {
      i = gen.uniform<int>(0, dst);
    }
    printf("%d %d %d\n", s, t, i);
  }

  return 0;
}
