#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "base.hpp"

int main(int, char *argv[]) {
  const long long case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 16074462832174510397ULL);

  int M = M_MIN;
  int N = N_MIN;
  int Q = Q_MIN;

  generate(gen, M, N, Q);

  return 0;
}
