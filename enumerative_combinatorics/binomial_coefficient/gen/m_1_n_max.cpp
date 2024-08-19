#include <iostream>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = 1;
  printf("%d %d\n", t, m);

  while (t--) {
    long long n, k;
    do {
      n = gen.uniform<long long>(0, N_MAX);
      k = gen.uniform<long long>(0, N_MAX);
    } while (n < k);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
