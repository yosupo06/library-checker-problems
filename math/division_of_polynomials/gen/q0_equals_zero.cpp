
#include "../params.h"
#include "random.h"
using namespace std;

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n, m;
  vector<int> f, g;

  if (seed % 3 == 0) {
    n = 3, m = 2;
    f = {1, 0, 1};
    g = {0, 1};
  }
  if (seed % 3 == 1) {
    n = N_MAX;
    m = n - 1;
    f.assign(n, 0);
    f[0] = f.back() = 1;
    g.assign(m, 0);
    g.back() = 1;
  }
  if (seed % 3 == 2) {
    n = N_MAX;
    m = N_MAX;
    f.assign(n, 0);
    g.assign(m, 0);
    for (int i = 0; i < n; ++i) f[i] = gen.uniform<int>(1, MOD - 1);
    for (int i = 0; i < m; ++i) g[i] = gen.uniform<int>(1, MOD - 1);
    g[0] = 0;
  }

  printf("%d %d\n", n, m);

  for (int i = 0; i < n; ++i) {
    if (i) printf(" ");
    printf("%d", f[i]);
  }
  printf("\n");

  for (int i = 0; i < m; ++i) {
    if (i) printf(" ");
    printf("%d", g[i]);
  }
  printf("\n");

  return 0;
}
