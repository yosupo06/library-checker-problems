#include <cmath>
#include <cstdlib>

#include "../params.h"
#include "random.h"

#include "output.hpp"

int main(int, char *argv[]) {
  const int case_number = std::atoll(argv[1]);
  Random rng(case_number ^ 0x5F07D122A12292CA);

  assert(case_number < 2);

  const int N = case_number;

  uniform_output(rng, N);
}
