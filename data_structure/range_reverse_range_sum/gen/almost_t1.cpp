#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0xA589E1553DF46248);

  const int N = N_MAX;
  const int Q = Q_MAX;

  output(rng, N, Q, 1);
}
