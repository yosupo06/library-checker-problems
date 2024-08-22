#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 500);
  int m = gen.uniform<int>(1, NM_MAX / n);
  if (seed % 2) swap(n, m);

  vector<vector<int>> a(n, vector<int>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { a[i][j] = gen.uniform<int>(0, MOD - 1); }
  }

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", a[i][j]);
      if (j + 1 != m) printf(" ");
    }
    printf("\n");
  }

  return 0;
}
