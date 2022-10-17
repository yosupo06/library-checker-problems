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

  int N = rnd.uniform(N_MIN, 1000LL);
  int M = rnd.uniform(M_MAX - 100000, M_MAX);
  printf("%d %d\n", N, M);

  for (int i = 0; i < M; i++) {
    int u = rnd.uniform<int>(0, N - 1);
    int v = rnd.uniform<int>(0, N - 1);
    printf("%d %d\n", u, v);
  }
  return 0;
}
