#include <cstdio>
#include "../params.h"
#include "random.h"
#include <vector>

#include "common.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int ns[] = {N_MAX, N_MAX, 1, 2};
  int ms[] = {1, 2, N_MAX, N_MAX};

  int n = ns[seed % 4];
  int m = ms[seed % 4];

  int LIM_1 = A_MAX / n;

  vector<ll> A = rand_gen(gen, n, -LIM_1, +LIM_1);
  vector<ll> B = rand_B(gen, m);
  out(A, B);

  return 0;
}
