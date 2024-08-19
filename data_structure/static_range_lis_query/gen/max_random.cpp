#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const int case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 6228176870498143928ULL);

  const int N = N_MAX;
  const int Q = Q_MAX;

  generate(gen, N, Q);

  return 0;
}
