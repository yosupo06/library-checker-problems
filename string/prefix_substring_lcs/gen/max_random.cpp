#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "base.hpp"

int main(int, char *argv[]) {
  const long long case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 10161799882718349619ULL);

  const int M = M_MAX;
  const int N = N_MAX;
  const int Q = Q_MAX;

  generate(gen, M, N, Q);

  return 0;
}
