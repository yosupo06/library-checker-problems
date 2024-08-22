#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  std::vector<int> par(N, -1);
  for (int i = 1; i < N; i++) {
    par[i] = gen.uniform(0, i - 1);
  }

  using edge = std::tuple<int, int, int>;
  std::vector<edge> edges;
  for (int i = 1; i < N; i++) {
    int c = gen.uniform(C_MIN, C_MAX);
    edges.emplace_back(i, par[i], c);
  }

  gen.shuffle(edges.begin(), edges.end());
  printf("%d\n", N);
  for (auto e : edges) {
    // auto [u, v, c] = e;
    int u, v, c;
    std::tie(u, v, c) = e;
    printf("%d %d %d\n", u, v, c);
  }

  return 0;
}
