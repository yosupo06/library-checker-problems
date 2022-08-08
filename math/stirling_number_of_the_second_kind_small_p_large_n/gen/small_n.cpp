#include <iostream>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int primes[] = {2, 3, 5, 7, 101, 4999};

  int T = T_MAX;
  int p = primes[seed % 6];
  printf("%d %d\n", T, p);

  int n_max = 5000;
  for (int t = 0; t < T; ++t) {
    long long n = gen.uniform<int>(0, n_max);
    long long k = gen.uniform<int>(0, n);
    printf("%lld %lld\n", n, k);
  }
  return 0;
}
