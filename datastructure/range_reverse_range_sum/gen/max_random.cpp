#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0x33EB099D0DFD35EE);

  const int N = N_MAX;
  const int Q = Q_MAX;

  output(rng, N, Q);
}
