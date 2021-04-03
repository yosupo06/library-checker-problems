#include "../params.h"
#include "./base.h"
#include "random.h"

int main(int, char *argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  const int n = gen.uniform(N_MIN / 2, N_MAX / 4) * 2;
  base(n, gen);
}
