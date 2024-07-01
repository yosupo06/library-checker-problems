#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = min(MAX_N, MAX_M);
  int m = n;

  auto P = gen.perm<int>(n);
  printf("%d %d\n", n, m);

  // vertex weight
  for (int i = 0; i < n; ++i) {
    if (i) printf(" ");
    int x = gen.uniform<int>(0, MOD - 1);
    printf("%d", x);
  }
  printf("\n");

  for (int i = 0; i < n; i++) {
    int a = P[i];
    int b = P[(i + 1) % n];
    printf("%d %d\n", a, b);
  }
  return 0;
}
