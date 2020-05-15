#include "../params.h"
#include "random.h"
#include <cstdio>
#include <vector>

void base(const int n, Random &gen) {
  std::vector<std::vector<int>> a(n, std::vector<int>(n));
  for (int i = 0; i != n; ++i) {
    a[i][i] = 0;
  }
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != i; ++j) {
      a[j][i] = gen.uniform<int>(0, MOD - 1);
      a[i][j] = a[j][i];
    }
  }

  std::printf("%d\n", n);
  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      std::printf("%d%c", a[i][j], " \n"[j + 1 == n]);
    }
  }
}
