#include <iostream>

#include "../params.h"
#include "random.h"
bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  long long t = T_MAX;
  long long m = -1;
  do {
    m = gen.uniform<long long>(100000, 1000000);
  } while (!is_prime(m));
  printf("%lld %lld\n", t, m);

  while (t--) {
    long long n, k;
    n = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    k = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
