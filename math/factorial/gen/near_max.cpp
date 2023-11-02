#include <cstdio>
#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(0.95 * MOD, MOD - 1);
  printf("%d\n", N);
  return 0;
}
