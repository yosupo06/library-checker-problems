#include <iostream>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  long long t = T_MAX;
  long long m = 998244353;
  long long q = 2;
  printf("%lld %lld %lld\n", t, m, q);

  while (t--) {
    long long n, k;
    n = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    k = gen.uniform<long long>(0, n - 1);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
