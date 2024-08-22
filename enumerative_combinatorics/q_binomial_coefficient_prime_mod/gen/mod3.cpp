#include <cstdlib>
#include <cstdio>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  long long t = T_MAX;
  long long m = 3;
  long long q = seed % 3;
  printf("%lld %lld %lld\n", t, m, q);

  while (t--) {
    long long n, k;
    n = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    k = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
