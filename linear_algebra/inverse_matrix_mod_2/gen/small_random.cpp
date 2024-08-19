#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int ns[] = {2, 2, 3, 3, 4, 4, 5, 5};
  int n = ns[seed % 8];

  vector<vector<int>> a(n, vector<int>(n));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { a[i][j] = gen.uniform<int>(0, MOD - 1); }
  }

  printf("%d\n", n);
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) { printf("%d", a[i][j]); }
    printf("\n");
  }
  return 0;
}
