#include <iostream>

#include "../params.h"
#include "random.h"

// 510510 = 2 * 3 * 5 * 7 * 11 * 13 * 17
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = 510510;
  printf("%d %d\n", t, m);

  while (t--) {
    long long n, k;
    do {
      n = gen.uniform<long long>(0, m);
      k = gen.uniform<long long>(0, m);
    } while (n < k);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
