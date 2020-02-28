#include <stdio.h>
#include "../params.h"
#include "../../../common/random.h"

int main(int, char **argv) {
  auto rng = Random(atoll(argv[1]));

  const int T = T_MAX;
  printf("%d\n", T);
  for (int t = 0; t < T; ++t) {
    const unsigned long long A = rng.uniform(0ULL, ~0ULL);
    const unsigned long long B = rng.uniform(0ULL, ~0ULL);
    printf("%llu %llu\n", A, B);
  }
  return 0;
}
