#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0x809E5421BFB3134B);

  const int N = rng.uniform<int>(std::sqrt(N_MAX) / 2, std::sqrt(N_MAX));
  const int Q = rng.uniform<int>(Q_MAX / 2, Q_MAX);

  output(rng, N, Q);
}
