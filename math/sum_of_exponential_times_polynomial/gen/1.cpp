#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../params.h"
#include "random.h"

using std::vector;

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed * 3 + 1);

  const long long R = 1;
  int D;
  long long N;
  switch (seed % 7) {
    case 0: D = 0; N = N_MAX; break;
    case 1: D = 5'000; N = D; break;
    case 2: D = 5'000; N = rng.uniform(D + 1, 10'000'000); break;
    case 3: D = D_MAX - 1; N = rng.uniform<long long>(D + 1, N_MAX); break;
    case 4: D = D_MAX; N = 0; break;
    case 5: D = D_MAX; N = D; break;
    case 6: D = D_MAX; N = N_MAX; break;
    default: assert(false);
  }
  printf("%lld %d %lld\n", R, D, N);
  return 0;
}
