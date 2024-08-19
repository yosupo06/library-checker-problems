#include "random.h"

#include <iostream>

#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(N_MAX / 2, N_MAX);
  int m = gen.uniform<int>(N_MAX / 2, N_MAX);
  int k = gen.uniform<int>(N_MAX / 2, N_MAX);

  printf("%d %d %d\n", n, m, k);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      printf("%d", gen.uniform<int>(0, MOD - 1));
      if (j + 1 != m) printf(" ");
    }
    printf("\n");
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) {
      printf("%d", gen.uniform<int>(0, MOD - 1));
      if (j + 1 != k) printf(" ");
    }
    printf("\n");
  }

  return 0;
}
