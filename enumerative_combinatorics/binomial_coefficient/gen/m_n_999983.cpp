#include <iostream>

#include "../params.h"
#include "random.h"

// 999983は10^6以下の最大の素数
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  int m = 999983;
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
