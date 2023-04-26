#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0x5F07D122A12292CA);

  assert(case_number < 8);
  const std::vector<int> r = {0, 1, -1};

  int M = r[case_number / 3];
  int N = r[case_number % 3];

  if (M == -1)
    M = rng.uniform<int>(std::sqrt(M_MAX), M_MAX);
  if (N == -1)
    N = rng.uniform<int>(N_MAX / 2, N_MAX);

  uniform_output(rng, M, N);
}
