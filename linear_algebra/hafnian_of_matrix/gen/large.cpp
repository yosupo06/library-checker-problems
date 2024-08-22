#include "../params.h"
#include "./base.h"
#include "random.h"

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  const int n = gen.uniform(N_MAX / 4, N_MAX / 2) * 2;
  base(n, gen);
}
