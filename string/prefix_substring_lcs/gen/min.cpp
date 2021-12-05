#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "base.hpp"

int main(int, char *argv[]) {
  const long long case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 16074462832174510397ULL);

  int M = gen.uniform<int>(M_MIN, M_MAX);
  int N = gen.uniform<int>(N_MIN, N_MAX);
  int Q = gen.uniform<int>(Q_MIN, Q_MAX);

  switch (case_index) {
  case 0: {
    M = M_MIN;
  } break;
  case 1: {
    N = N_MIN;
  } break;
  case 2: {
    Q = Q_MIN;
  } break;
  }

  generate(gen, M, N, Q);

  return 0;
}
