#include <cstdio>

#include "../params.h"
#include "random.h"

void output(const std::vector<int> &f, const std::vector<int> &s) {
  const int M = f.size();
  const int N = __builtin_ctz(s.size());
  printf("%d %d\n", M, N);
  for (int i = 0; i < M; i++) {
    if (i)
      printf(" ");
    printf("%d", f[i]);
  }
  printf("\n");
  for (int i = 0; i < 1 << N; i++) {
    if (i)
      printf(" ");
    printf("%d", s[i]);
  }
  printf("\n");
}

void uniform_output(Random &rng, const int M, const int N) {
  std::vector<int> f(M), s(1 << N);
  for (auto &e : f)
    e = rng.uniform<int>(0, MOD - 1);
  for (auto &e : s)
    e = rng.uniform<int>(0, MOD - 1);
  output(f, s);
}
