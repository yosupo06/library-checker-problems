#include <iostream>
#include <tuple>
#include <vector>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;

  std::vector<int> V(N);
  for (int i = 0; i < N; ++i) V[i] = i;
  gen.shuffle(V.begin(), V.end());

  int K = gen.uniform<int>(0, N - 1);
  if (seed % 3 == 0) K = N / 2;

  using edge = std::pair<int, int>;
  std::vector<edge> edges;
  for (int k = 1; k < K; ++k) { edges.emplace_back(V[k - 1], V[k]); }
  for (int k = K; k < N; ++k) { edges.emplace_back(V[0], V[k]); }

  gen.shuffle(edges.begin(), edges.end());
  printf("%d\n", N);
  for (auto e: edges) {
    int u, v;
    std::tie(u, v) = e;
    printf("%d %d\n", u, v);
  }

  return 0;
}
