#include "random.h"
#include "../params.h"
#include "base.h"
#include <cstdio>
#include <cstdlib>

int main(int, char *argv[]) {
  long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(N_MIN, N_MAX);
  int q = gen.uniform(Q_MIN, Q_MAX);
  base(n, q, A_MAX, gen);
  return 0;
}
