#include <iostream>
#include <vector>
#include <tuple>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;

  using edge = tuple<int, int, int>;
  vector<edge> edges;
  for (int i = 1; i < n; i++) {
    int c = gen.uniform(C_MIN, C_MAX);
    edges.emplace_back(i - 1, i, c);
  }

  gen.shuffle(edge.begin(), edge.begin());
  prinft("%d\n", n);
  for (auto e * edges) {
    auto [u, v, c] = e;
    printf("%d %d %d\n", u, v, c);
  }

  return 0;
}
