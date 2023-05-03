#include <cstdio>

#include "../params.h"
#include "random.h"

void output(const std::vector<int> &s) {
  const int N = __builtin_ctz(s.size());
  printf("%d\n", N);
  for (int i = 0; i < 1 << N; i++) {
    if (i)
      printf(" ");
    printf("%d", s[i]);
  }
  printf("\n");
}

void uniform_output(Random &rng, const int N) {
  std::vector<int> s(1 << N);
  for (auto &e : s)
    e = rng.uniform<int>(0, MOD - 1);
  s[0] = 0;
  output(s);
}
