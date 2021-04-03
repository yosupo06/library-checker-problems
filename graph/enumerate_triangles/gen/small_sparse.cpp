#include "../params.h"
#include "./erdos_renyi.h"
#include "random.h"
#include <algorithm>

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N_MAX_2 = 1;
  while (N_MAX_2 < N_MAX && N_MAX_2 * (N_MAX_2 + 1) / 2 <= M_MAX) {
    N_MAX_2 += 1;
  }

  int n = gen.uniform<int>(N_MIN, N_MAX_2);
  int m =
      gen.uniform<int>(M_MIN, std::min<int>({M_MAX, n * 2, n * (n - 1) / 2}));

  erdos_renyi(n, m, gen);
}
