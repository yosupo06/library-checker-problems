#include "random.h"

#include <iostream>

#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = N_MAX;
  int k = N_MAX;

  printf("%d %d %d\n", n, m, k);

  auto get = [&]() -> int {
    int k = gen.uniform<int>(0, 1000);
    return (k == 0 ? 0 : 1);
  };

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) { printf("%d", get()); }
    printf("\n");
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < k; j++) { printf("%d", get()); }
    printf("\n");
  }

  return 0;
}
