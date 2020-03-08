#include <stdio.h>
#include <stdlib.h>
#include "../params.h"
#include "random.h"

constexpr int DS[] = {0, 1, 10'000, 500'000, D_MAX - 1, D_MAX};
constexpr int DSLEN = sizeof(DS) / sizeof(DS[0]);

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed);

  const long long R = rng.uniform(2LL, MOD - 1);
  const int D = DS[seed % DSLEN];
  printf("%lld %d\n", R, D);
  return 0;
}
