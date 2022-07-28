#include <cstdlib>
#include <cstdio>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;

  std::printf("%d\n", n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::printf("%d", gen.uniform<int>(0, MOD - 1));
      if (j != n - 1) std::printf(" ");
    }
    std::printf("\n");
  }

  return 0;
}
