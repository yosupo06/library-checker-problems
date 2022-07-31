#include "random.h"
#include "../params.h"
#include <iostream>

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = seed % 10 + 1;
  int q = 1000;
  printf("%d %d\n", n, q);
  vector<int> P = gen.perm<int>(n);
  for (int i = 0; i < n; i++) {
    int p = P[i];
    int a = gen.uniform<int>(1, MOD - 1);
    int b = gen.uniform<int>(0, MOD - 1);
    printf("%d %d %d\n", p, a, b);
  }
  for (int i = 0; i < q; i++) {
    int t = gen.uniform(0, 3);
    if (t == 0) {
      int i = gen.uniform<int>(0, n - 1);
      int a = gen.uniform<int>(1, MOD - 1);
      int b = gen.uniform<int>(0, MOD - 1);
      printf("%d %d %d %d\n", t, i, a, b);
    }
    if (t == 1) {
      auto p = gen.uniform_pair<int>(0, n);
      int x = gen.uniform<int>(0, MOD - 1);
      printf("%d %d %d %d\n", t, p.first, p.second, x);
    }
    if (t == 2 || t == 3) {
      auto p = gen.uniform_pair<int>(0, n);
      printf("%d %d %d\n", t, p.first, p.second);
    }
  }
  return 0;
}
