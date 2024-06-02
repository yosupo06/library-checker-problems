#include <cstdlib>
#include <cstdio>

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
  do { m = gen.uniform<long long>(100000000, M_MAX); } while (!is_prime(m));
  long long q = seed % 2;
  printf("%lld %lld %lld\n", t, m, q);

  while (t--) {
    long long n, k;
    n = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    k = gen.uniform<long long>(0, std::min(m, N_MAX) - 1);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
