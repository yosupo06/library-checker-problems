#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "base.hpp"

int main(int, char *argv[]) {
  const long long case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 4375081899707405098ULL);

  const int M = gen.uniform<int>(M_MIN, std::min<int>(M_MAX, 300));
  const int N = gen.uniform<int>(N_MIN, std::min<int>(N_MAX, 300));
  const int Q = Q_MAX;

  generate(gen, M, N, Q);

  return 0;
}
