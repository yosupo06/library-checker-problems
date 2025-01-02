#include <iostream>
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int zero = 20;
  int n = (1 << 17) - zero;
  int m = (1 << 17);
  vector<int> a(n + zero), b(m);

  for (int i = 0; i < n; i++) { a[i] = gen.uniform((i != n - 1) ? 0 : 1, 998244352); }
  for (int i = 0; i < m; i++) { b[i] = gen.uniform(0, 998244352); }

  const int MOD = 998244353;
  for (int i = 0; i < zero; i++) {
    int v = gen.uniform(0, 998244353);
    if (i < 10)
      b[gen.uniform(0, m)] = (MOD - v) % MOD;
    else
      b[i] = (MOD - v) % MOD;
    for (int j = n - 1; j >= 0; j--) {
      a[j + 1] = (a[j + 1] + a[j]) % MOD;
      a[j] = (long long)(a[j]) * (long long)(v) % MOD;
    }
    n++;
  }

  printf("%d %d\n", n, m);

  for (int i = 0; i < n; i++) {
    printf("%d", a[i]);
    if (i != n - 1) printf(" ");
  }
  printf("\n");
  for (int i = 0; i < m; i++) {
    printf("%d", b[i]);
    if (i != m - 1) printf(" ");
  }
  printf("\n");
  return 0;
}