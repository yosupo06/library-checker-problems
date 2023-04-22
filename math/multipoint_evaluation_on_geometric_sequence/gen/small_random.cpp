#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 100);
  int m = gen.uniform<int>(1, 100);
  int a = gen.uniform<int>(0, MOD - 1);
  int r = gen.uniform<int>(0, MOD - 1);

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
