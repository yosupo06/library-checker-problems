#include <cstdio>
#include <numeric>
#include <tuple>
#include <utility>
#include <vector>

#include "random.h"

void generate(Random &gen, const int N, const int Q) {
  std::vector<int> P(N);
  std::iota(P.begin(), P.end(), 0);
  gen.shuffle(P.begin(), P.end());

  std::vector<std::pair<int, int>> qs(Q);
  for (auto &[l, r] : qs) {
    std::tie(l, r) = gen.uniform_pair(0, N + 1);
    r -= 1;
  }

  std::printf("%d %d\n", N, Q);
  for (int i = 0; i < N; i++) {
    std::printf("%d%c", P[i], " \n"[i + 1 == N]);
  }
  for (const auto &[l, r] : qs) {
    std::printf("%d %d\n", l, r);
  }
}
