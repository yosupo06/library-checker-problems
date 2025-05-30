#include "random.h"
#include <cstdio>

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = seed % 500 + 1;
  int Q = 1000;
  printf("%d %d\n", N, Q);

  int cand = gen.uniform(0, 1'000'000'000);
  for (int i = 0; i < N; ++i) {
    if (i) {
      printf(" ");
    }
    if (gen.uniform_bool()) {
      printf("%d", cand);
    } else {
      printf("%d", gen.uniform(0, 1'000'000'000));
    }
  }
  printf("\n");

  for (int i = 0; i < Q; ++i) {
    int t = gen.uniform(0, 1);
    printf("%d ", t);
    if (t == 0) {
      int p = gen.uniform(0, N - 1);
      int x = gen.uniform_bool() ? cand : gen.uniform(0, 1'000'000'000);
      printf("%d %d\n", p, x);
    } else {
      auto [l, r] = gen.uniform_pair(0, N);
      printf("%d %d\n", l, r);
    }
  }

  return 0;
}