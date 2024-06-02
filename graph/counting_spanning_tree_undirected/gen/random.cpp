#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(N_MIN, N_MAX);
  int M = gen.uniform<int>(M_MIN, M_MAX);
  printf("%d %d\n", N, M);
  for (int i = 0; i < M; ++i) {
    int a = gen.uniform<int>(0, N - 1);
    int b = gen.uniform<int>(0, N - 1);
    printf("%d %d\n", a, b);
  }
  return 0;
}
