#include <iostream>

#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, 128);
  int m = gen.uniform<int>(1, 128);
  int k = gen.uniform<int>(1, 128);

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
