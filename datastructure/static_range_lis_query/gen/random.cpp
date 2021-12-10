#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const int case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 13428581043660426568ULL);

  const int N = gen.uniform<int>(N_MIN, N_MAX);
  const int Q = gen.uniform<int>(Q_MIN, Q_MAX);

  generate(gen, N, Q);

  return 0;
}
