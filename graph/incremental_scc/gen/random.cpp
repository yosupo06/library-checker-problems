#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(MIN_N, MAX_N);
  int m = MAX_M;
  printf("%d %d\n", n, m);

  // vertex weight
  for (int i = 0; i < n; ++i) {
    if (i) printf(" ");
    int x = gen.uniform<int>(0, MOD - 1);
    printf("%d", x);
  }
  printf("\n");

  for (int i = 0; i < m; i++) {
    int a = gen.uniform(0, n - 1);
    int b = gen.uniform(0, n - 1);
    printf("%d %d\n", a, b);
  }
  return 0;
}
