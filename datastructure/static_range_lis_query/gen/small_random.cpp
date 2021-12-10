#include <algorithm>
#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const int case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 584641959168880510ULL);

  const int N = gen.uniform<int>(N_MIN, std::min<int>(1000, N_MAX));
  const int Q = gen.uniform<int>(Q_MIN, std::min<int>(1000, Q_MAX));

  generate(gen, N, Q);

  return 0;
}
