#include "../params.h"
#include "base.h"
#include "random.h"
#include <cstdio>
#include <cstdlib>

int main(int, char *argv[]) {
  long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int q = Q_MAX;
  base(n, q, A_MAX, gen);
  return 0;
}
