#include <stdio.h>
#include <tuple>
#include "random.h"
#include "../params.h"

long long TEN(int e) {
  assert(0 <= e && e <= 18);
  long long res = 1;
  while (e) res *= 10, --e;
  return res;
}

// https://judge.yosupo.jp/hack/299
// make_worstcase
// swap(x,y) したものも含めて 2 ケース
int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX, q = Q_MAX;
  printf("%d %d\n", n, q);

  for (int i = 0; i < n; ++i) {
    int x = gen.uniform<int>(0, TEN(9) - 1);
    int y = gen.uniform<int>(0, 99);
    if (seed & 1) std::swap(x, y);
    int w = gen.uniform<int>(0, MOD - 1);
    printf("%d %d %d\n", x, y, w);
  }

  for (int j = 0; j < q; ++j) {
    int tp = (gen.uniform<int>(0, 9) ? 3 : 2);
    int l = gen.uniform<int>(0, 99);
    int r = TEN(9) - gen.uniform<int>(0, 99);
    int d = gen.uniform<int>(0, 99);
    int u = gen.uniform<int>(0, 99);
    if (d > u) std::swap(d, u);
    u++;

    if (seed & 1) std::swap(l, d), std::swap(r, u);

    int a = gen.uniform<int>(0, MOD - 1);
    int b = gen.uniform<int>(0, MOD - 1);

    if (tp == 3) {
      printf("%d %d %d %d %d %d %d\n", tp, l, d, r, u, a, b);
    } else {
      printf("%d %d %d %d %d\n", tp, l, d, r, u);
    }
  }
}
