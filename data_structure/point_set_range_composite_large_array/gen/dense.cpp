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

  int ws[] = {1, 1000, 1000000};
  int w = ws[seed % 3];

  int L = gen.uniform<int>(0, n - w);
  int R = L + w;

  auto idx = [&]() -> int { return gen.uniform<int>(L, R - 1); };

  auto idx2 = [&]() -> pair<int, int> {
    int a = idx(), b = idx();
    if (a > b) swap(a, b);
    ++b;
    return {a, b};
  };

  for (int i = 0; i < q; i++) {
    int t = gen.uniform(0, 1);
    printf("%d ", t);
    if (t == 0) {
      int p = idx();
      int c = gen.uniform(1LL, MOD - 1);
      int d = gen.uniform(0LL, MOD - 1);
      printf("%d %d %d\n", p, c, d);
    } else {
      auto [a, b] = idx2();
      int x = gen.uniform(0LL, MOD - 1);
      printf("%d %d %d\n", a, b, x);
    }
  }
  return 0;
}
