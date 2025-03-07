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

  int ws[] = {1, 1000, 500000};
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
    auto p = idx2();

    if (t == 0) {
      int b = gen.uniform(1LL, MOD - 1);
      int c = gen.uniform(0LL, MOD - 1);
      printf("%d %d %d %d %d\n", t, p.first, p.second, b, c);
    } else {
      printf("%d %d %d\n", t, p.first, p.second);
    }
  }
  return 0;
}
