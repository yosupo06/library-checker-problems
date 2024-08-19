#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0x4B9309FBABA7C666);

  assert(case_number < 8);
  const std::vector<int> r = {0, 1, -1};

  int N = r[case_number / 3];
  int Q = r[case_number % 3];

  if (N == -1)
    N = rng.uniform<int>(N_MAX / 2, N_MAX);
  if (Q == -1)
    Q = rng.uniform<int>(Q_MAX / 2, Q_MAX);

  output(rng, N, Q);
}
