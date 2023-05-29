#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0xCBDA239552CD1593);

  const int N = rng.uniform<int>(N_MAX / 4, N_MAX / 2);

  uniform_output(rng, N);
}
