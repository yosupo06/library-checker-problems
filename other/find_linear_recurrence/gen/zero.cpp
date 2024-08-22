#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "random.h"
#include "../params.h"

using std::vector;

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed);

  const int N = N_MAX;
  vector<long long> as(N, 0);
  if (seed % 2 != 0) {
    as[N - 1] = rng.uniform(1LL, MOD - 1);
  }

  printf("%d\n", N);
  for (int i = 0; i < N; ++i) {
    if (i > 0) printf(" ");
    printf("%lld", as[i]);
  }
  puts("");
  return 0;
}
