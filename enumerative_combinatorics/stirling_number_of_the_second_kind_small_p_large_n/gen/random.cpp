#include <iostream>

#include "../params.h"
#include "random.h"

bool is_prime(int p) {
  if (p <= 1) return false;
  for (int i = 2; i < p; ++i)
    if (p % i == 0) return false;
  return true;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int T = T_MAX;
  int p;
  while (1) {
    p = gen.uniform<int>(P_MIN, P_MAX);
    if (is_prime(p)) break;
  }
  printf("%d %d\n", T, p);

  for (int t = 0; t < T; ++t) {
    long long n = gen.uniform<long long>(0, N_MAX);
    long long k = gen.uniform<long long>(0, n);
    printf("%lld %lld\n", n, k);
  }
  return 0;
}
