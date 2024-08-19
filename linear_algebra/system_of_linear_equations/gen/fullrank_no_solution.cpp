#include <iostream>
#include <numeric>

#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int m = gen.uniform(1, 500);
  int n = gen.uniform(m, 500);
  int MOD = 998244353;

  vector<vector<long long>> a(n, vector<long long>(m + 1));
  for (int i = 0; i < m; i++) {
    for (int j = 0; j <= m; j++) {
      a[i][j] = gen.uniform(0, 998244353 - 1);
    }
  }
  for (int i = m; i < n; i++) {
    for (int ii = 0; ii < m; ii++) {
      long long freq = gen.uniform(0, 998244353 - 1);
      if (gen.uniform(0, 1) == 1) {
        for (int j = 0; j <= m; j++) {
          a[i][j] += a[ii][j] * freq;
          a[i][j] %= MOD;
        }
      }
    }
  }
  a[0][m] = (a[0][m] + 1) % MOD;
  gen.shuffle(begin(a), end(a));

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%lld", a[i][j]);
      if (j + 1 != m) printf(" ");
    }
    printf("\n");
  }
  for (int i = 0; i < n; i++) {
    printf("%lld", a[i][m]);
    if (i + 1 != n) printf(" ");
  }
  printf("\n");

  return 0;
}
