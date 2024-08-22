#include <stdio.h>
#include "../params.h"
#include "random.h"

constexpr int N_AND_M = 354294;

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed);

  const int N = N_AND_M;
  const int M = N_AND_M;

  printf("%d %d\n", N, M);
  for (int i = 0; i < N; ++i) {
    if (i > 0) printf(" ");
    printf("%llu", rng.uniform(0ULL, ~0ULL));
  }
  puts("");
  for (int i = 0; i < M; ++i) {
    if (i > 0) printf(" ");
    printf("%llu", rng.uniform(0ULL, ~0ULL));
  }
  puts("");
  return 0;
}
