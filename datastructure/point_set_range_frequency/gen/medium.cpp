#include <cstdlib>

#include "../params.h"
#include "base.hpp"
#include "random.h"

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  int ks[] = {1, 2, 5, 100, 1000};

  int N = gen.uniform<int>(100, 1000);
  int Q = Q_MAX;
  int K = ks[seed % 5];
  generate(gen, N, Q, K, 50);
  return 0;
}
