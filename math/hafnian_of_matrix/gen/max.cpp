#include "../params.h"
#include "./base.h"
#include "random.h"

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  const int n = N_MAX;
  base(n, gen);
}
