#include <cstdio>
#include <cstdlib>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 4096);
  int m = gen.uniform<int>(1, NM_MAX / n);
  if (seed % 2) swap(n, m);

  vector<string> a(n, string(m, '0'));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      a[i][j] = '0' + gen.uniform<int>(0, MOD - 1);
    }
  }

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) { printf("%s\n", a[i].c_str()); }

  return 0;
}
