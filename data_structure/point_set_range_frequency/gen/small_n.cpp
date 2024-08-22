#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  const int N = N_MIN + seed;
  generate(gen, N, Q_MAX, 10, 50);
  return 0;
}
