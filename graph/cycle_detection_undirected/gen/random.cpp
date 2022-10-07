#include <cstdio>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto rnd = Random(seed);

  int N = rnd.uniform(N_MIN, N_MAX);
  int M = rnd.uniform(M_MIN, M_MAX);
  printf("%d %d\n", N, M);

  for (int i = 0; i < M; i++) {
    int u = rnd.uniform<int>(0, N - 1);
    int v = rnd.uniform<int>(0, N - 1);
    printf("%d %d\n", u, v);
  }
  return 0;
}
