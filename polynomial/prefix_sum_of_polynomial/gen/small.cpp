#include <cstdio>
#include <cstdlib>

#include "../params.h"
#include "random.h"

int main(int, char *argv[]) {
  long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  const int N_SMALL = 100;
  const int n = gen.uniform<int>(1, N_SMALL);
  std::printf("%d\n", n);

  for (int i = 0; i < n; ++i) {
    if (i)
      std::printf(" ");
    std::printf("%d", gen.uniform<int>(0, MOD - 1));
  }
  std::puts("");

  return 0;
}
