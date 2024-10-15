#include <cstdio>
#include "../params.h"
#include "random.h"
#include <vector>

#include "common.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(1, N_MAX);
  int m = gen.uniform<int>(1, N_MAX);

  int LIM_1 = A_MAX / n * 3;

  vector<ll> A = rand_gen(gen, n, -LIM_1, +LIM_1);
  vector<ll> B = rand_B(gen, m);
  upside_down(A);
  out(A, B);

  return 0;
}
