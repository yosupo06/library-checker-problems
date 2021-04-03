#include "../params.h"
#include "random.h"
#include <cstdio>
#include <utility>

void base(int n, int q, int a, Random &gen) {
  std::printf("%d %d\n", n, q);
  for (int i = 0; i != n; ++i) {
    if (i != 0) {
      std::printf(" ");
    }
    std::printf("%d", gen.uniform<int>(A_MIN, a));
  }
  std::printf("\n");
  for (int i = 0; i != q; ++i) {
    auto lr = gen.uniform_pair(0, n);
    std::printf("%d %d\n", lr.first, lr.second);
  }
}
