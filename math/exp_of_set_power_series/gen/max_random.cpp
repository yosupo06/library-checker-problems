#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0xD2DD0DC5001EB97E);

  const int N = N_MAX;

  uniform_output(rng, N);
}
