#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  const int N = N_MIN + seed;
  if (N == 0) {
    generate(gen, N, Q_MAX, 0, 0);
  } else {
    generate(gen, N, Q_MAX, N, 0.9);
  }

  return 0;
}
