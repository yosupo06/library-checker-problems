#include <cstdio>
#include "common.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(0, 10);
  int m = gen.uniform<int>(0, n);
  int k = 0;
  if (m > 0) k = gen.uniform<int>(1, m);
  gen_and_out(gen, n, m, k);

  return 0;
}
