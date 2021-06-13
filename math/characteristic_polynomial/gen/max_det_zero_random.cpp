#include <cstdlib>
#include <cstdio>
#include <vector>

#include "../params.h"
#include "random.h"

int main(int, char* argv[]) {
  long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;

  std::printf("%d\n", n);

  unsigned long long v = gen.uniform<int>(0, MOD - 1);
  std::pair<int, int> k = gen.uniform_pair<int>(0, n - 1);

  std::vector<int> picked_row(n);

  for (int i = 0; i < n; ++i) {
    if (i == k.second) {
      for (int j = 0; j < n; ++j) {
        std::printf("%d", int(v * picked_row[j] % MOD));
        if (j != n - 1) std::printf(" ");
      }
    } else {
      for (int j = 0; j < n; ++j) {
        int rv = gen.uniform<int>(0, MOD - 1);
        std::printf("%d", rv);
        if (j != n - 1) std::printf(" ");
        if (i == k.first) picked_row[j] = rv;
      }
    }
    std::printf("\n");
  }
  return 0;
}
