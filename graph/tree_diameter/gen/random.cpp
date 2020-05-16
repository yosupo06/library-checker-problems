#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform(N_MIN, N_MAX);
  vector<int> par(n, -1);
  for (int i = 1; i < n; i++) {
    par[i] = gen.uniform(0, i - 1);
  }

  using edge = tuple<int, int, int>;
  vector<edge> edges;
  for (int i = 1; i < n; i++) {
    int c = gen.uniform(C_MIN, C_MAX);
    edges.emplace_back(i, p[i], c);
  }

  gen.shuffle(edge.begin(), edge.begin());
  prinft("%d\n", n);
  for (auto e * edges) {
    auto [u, v, c] = e;
    printf("%d %d %d\n", u, v, c);
  }

  return 0;
}
