#include "random.h"
#include <iostream>
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int q;
  vector<int> ts;
  if (seed == 0) { q = 1, ts = {0}; }
  if (seed == 1) { q = 1, ts = {1}; }
  if (seed == 2) { q = 2, ts = {0, 0}; }
  if (seed == 3) { q = 2, ts = {0, 1}; }
  if (seed == 4) { q = 2, ts = {1, 0}; }
  if (seed == 5) { q = 2, ts = {1, 1}; }

  printf("%d %d\n", n, q);
  for (int i = 0; i < q; i++) {
    int t = ts[i];
    auto p = gen.uniform_pair(0, n);
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
