#include "random.h"
#include <iostream>
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int q = Q_MAX;
  printf("%d %d\n", n, q);
  for (int i = 0; i < q; i++) {
    int t = (i < q / 2 ? 0 : 1);
    if (gen.uniform<int>(0, 100) == 0) t = 1 - t;
    printf("%d ", t);
    if (t == 0) {
      int p = gen.uniform(0, n - 1);
      int c = gen.uniform(1LL, MOD - 1);
      int d = gen.uniform(0LL, MOD - 1);
      printf("%d %d %d\n", p, c, d);
    } else {
      auto p = gen.uniform_pair(0, n);
      int x = gen.uniform(0LL, MOD - 1);
      printf("%d %d %d\n", p.first, p.second, x);
    }
  }
  return 0;
}
