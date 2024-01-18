#include <stdio.h>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

tuple<int, int, int, int, int> random_rect(Random& gen) {
  auto [l, r] = gen.uniform_pair<int>(0, COORD_MAX);
  auto [d, u] = gen.uniform_pair<int>(0, COORD_MAX);
  int w = gen.uniform<int>(0, WEIGHT_MAX);
  return {l, d, r, u, w};
}

pair<int, int> random_pt(Random& gen) {
  int x = gen.uniform<int>(0, COORD_MAX);
  int y = gen.uniform<int>(0, COORD_MAX);
  return {x, y};
}

int main(int, char** argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int q = Q_MAX;
  printf("%d %d\n", n, q);

  for (int i = 0; i < n; i++) {
    auto [l, d, r, u, w] = random_rect(gen);
    printf("%d %d %d %d %d\n", l, d, r, u, w);
  }
  for (int i = 0; i < q; i++) {
    bool rect = gen.uniform<int>(0, 10) > 0;
    if (rect) {
      auto [l, d, r, u, w] = random_rect(gen);
      printf("%d %d %d %d %d %d\n", 0, l, d, r, u, w);
    } else {
      auto [x, y] = random_pt(gen);
      printf("%d %d %d\n", 1, x, y);
    }
  }
  return 0;
}
