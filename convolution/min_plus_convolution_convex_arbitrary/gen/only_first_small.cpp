#include <cstdio>
#include "../params.h"
#include "random.h"
#include <vector>

#include "common.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = N_MAX;

  int LIM_1 = A_MAX / n * 3;

  vector<ll> A = rand_gen(gen, n, -LIM_1, +LIM_1);
  vector<ll> B(m);
  for (int i = 0; i < m; ++i) {
    B[i] = gen.uniform<int>(A_MAX * 9 / 10, A_MAX);
  }

  int idx = (seed % 2 == 0 ? 0 : m - 1);
  B[idx] = A_MIN;

  out(A, B);

  return 0;
}
