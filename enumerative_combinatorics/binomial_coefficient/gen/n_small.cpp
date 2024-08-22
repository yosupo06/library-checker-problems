#include <iostream>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = gen.uniform<int>(1, M_MAX);
  printf("%d %d\n", t, m);

  int small_n_max = 2000;
  while (t--) {
    long long n, k;
    do {
      n = gen.uniform<int>(0, small_n_max);
      k = gen.uniform<int>(0, small_n_max);
    } while (n < k);
    printf("%lld %lld\n", n, k);
  }
  return 0;
}
