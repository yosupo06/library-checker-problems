#include "../params.h"
#include "random.h"
#include <cassert>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform(1, 100);
  int T = gen.uniform(T_MAX - 100, T_MAX);
  printf("%d %d\n", N, T);
  for (int i = 0; i < N; i++) {
    printf("%d", gen.uniform(1, T));
    if (i != N - 1)
      printf(" ");
  }
  printf("\n");
  return 0;
}
