#include "../params.h"
#include "random.h"
#include <cstdio>
#include <cstdlib>
#include <vector>

int main(int, char *argv[]) {

  const long long seed = std::atoll(argv[1]);
  auto gen = Random(seed);

  const int N = N_MAX;
  int M = 0;
  while (true) {
    const int next_M = M * 2 + 1;
    if (next_M <= M_MAX) {
      M = next_M;
    } else {
      break;
    }
  }

  std::vector<int> a(N);
  a[0] = gen.uniform<int>(2, MOD - 1);
  for (int i = 1; i < N; i++) {
    a[i] = gen.uniform<int>(0, MOD - 1);
  }

  std::printf("%d %d\n", N, M);
  for (int i = 0; i < N; i++) {
    std::printf("%d%c", a[i], " \n"[i + 1 == N]);
  }

  return 0;
}
