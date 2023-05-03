#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0x0D11F6E8AA9D7808);

  const int N = rng.uniform<int>(N_MAX / 2, N_MAX);

  uniform_output(rng, N);
}
