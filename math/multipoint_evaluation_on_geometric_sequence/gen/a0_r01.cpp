#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<int> as = {0, 0, 0, -1, -1};
  vector<int> rs = {0, 1, -1, 0, 1};

  int n = NM_MAX;
  int m = NM_MAX;
  int a = as[seed % 5];
  int r = rs[seed % 5];
  if (a == -1) a = gen.uniform<int>(0, MOD - 1);
  if (r == -1) r = gen.uniform<int>(0, MOD - 1);

  vector<int> f(n);
  for (int i = 0; i < n; ++i) f[i] = gen.uniform<int>(0, MOD - 1);

  printf("%d %d %d %d\n", n, m, a, r);
  for (int i = 0; i < n; i++) {
    if (i) printf(" ");
    printf("%d", f[i]);
  }
  printf("\n");
  return 0;
}
