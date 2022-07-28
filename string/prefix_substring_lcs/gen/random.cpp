#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "base.hpp"

int main(int, char *argv[]) {
  const long long case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 5806102363372628857ULL);

  const int M = gen.uniform<int>(M_MIN, M_MAX);
  const int N = gen.uniform<int>(N_MIN, N_MAX);
  const int Q = gen.uniform<int>(Q_MIN, Q_MAX);

  generate(gen, M, N, Q);

  return 0;
}
