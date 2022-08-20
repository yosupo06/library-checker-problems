#include "../params.h"
#include "./erdos_renyi.h"
#include "random.h"

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MIN;
  while (n < N_MAX && n * (n + 1) / 2 <= M_MAX) {
    n += 1;
  }
  int m = n * (n - 1) / 2;

  erdos_renyi(n, m, gen);
}
