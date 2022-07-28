#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  const int Q = Q_MIN + seed;

  generate(gen, N_MAX, Q, std::sqrt(N_MAX), 0.9);

  return 0;
}
