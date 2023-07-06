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

  vector<ll> A = rand_gen(gen, n, -10, +10);
  vector<ll> B = rand_B(gen, m);
  out(A, B);

  return 0;
}
