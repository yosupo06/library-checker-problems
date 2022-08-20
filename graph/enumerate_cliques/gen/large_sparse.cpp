#include "../params.h"
#include "./erdos_renyi.h"
#include "random.h"
#include <algorithm>

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(10, 20);
  int m = gen.uniform<int>(
      (int)(std::min(M_MAX, static_cast<long long>(n) * (n - 1) / 2) * 0.9), std::min(M_MAX, static_cast<long long>(n) * (n - 1) / 2));

  erdos_renyi(n, m, gen);
}
