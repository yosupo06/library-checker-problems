#include <cstdlib>
#include <cstdio>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  const int N_SMALL = 100;
  int n = gen.uniform<int>(1, N_SMALL);
  int m = gen.uniform<int>(1, N_SMALL);
  int c = gen.uniform<int>(0, MOD - 1);
  std::printf("%d %d %d\n", n, m, c);

  for (int i = 0; i < n; ++i) {
    std::printf("%d", gen.uniform<int>(0, MOD - 1));
    if (i != n - 1) std::printf(" ");
  }
  std::printf("\n");

  return 0;
}