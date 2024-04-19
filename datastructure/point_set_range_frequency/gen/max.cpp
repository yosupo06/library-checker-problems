#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  int ks[] = {1, 2, 5, 100, 1000, 10000, N_MAX, 10 * N_MAX};

  int N = N_MAX;
  int Q = Q_MAX;
  int K = ks[seed % 8];
  generate(gen, N, Q, K, 0.5);
  return 0;
}
