#include <cstdio>

#include "../params.h"
#include "random.h"

void output(Random &rng, const int N, const int Q, const int t_default = -1) {
  printf("%d %d\n", N, Q);
  for (int i = 0; i < N; i++) {
    if (i)
      printf(" ");
    printf("%d", rng.uniform<int>(0, A_MAX));
  }
  printf("\n");
  for (int j = 0; j < Q; j++) {
    int t = t_default;
    if (t == -1 ||  rng.uniform01() <= 0.01) {
      t = rng.uniform<int>(0, 1);
    }
    const auto [l, r] = rng.uniform_pair<int>(0, N + 1);
    printf("%d %d %d\n", t, l, r - 1);
  }
}
