#include "../params.h"
#include "./erdos_renyi.h"
#include "random.h"

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = M_MAX;

  erdos_renyi(n, m, gen);
}
