#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "../params.h"
#include "random.h"

using std::vector;

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  // auto rng = Random(seed * 3 + 0);

  const long long R = 0;
  int D;
  long long N;
  switch (seed % 5) {
    case 0: D = 0; N = 0; break;
    case 1: D = 0; N = 1; break;
    case 2: D = D_MAX; N = 0; break;
    case 3: D = D_MAX; N = 1; break;
    case 4: D = D_MAX; N = N_MAX; break;
    default: assert(false);
  }
  printf("%lld %d %lld\n", R, D, N);
  return 0;
}
