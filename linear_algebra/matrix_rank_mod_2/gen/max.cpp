#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int ns[] = {1, 2, 3, 4095, 4096, 4097, NM_MAX / 3, NM_MAX / 2, NM_MAX / 1};
  int n = ns[seed % 9];
  int m = NM_MAX / n;

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
