#include <cstdlib>

#include "../params.h"
#include "random.h"
#include <tuple>

int main(int, char *argv[]) {
  const int case_index = std::atoll(argv[1]);
  Random gen(case_index ^ 134268020235868123ULL);

  const int N = N_MAX;
  const int Q = Q_MAX;

  std::vector<int> P;
  for (int i = N / 2; i <= N; ++i) P.emplace_back(i);
  for (int i = 1; i < N / 2; ++i) P.emplace_back(i);
  for (auto &x: P) --x;

  std::vector<std::pair<int, int>> qs(Q);
  for (auto &[l, r]: qs) {
    std::tie(l, r) = gen.uniform_pair(0, N + 1);
    r -= 1;
  }

  std::printf("%d %d\n", N, Q);
  for (int i = 0; i < N; i++) { std::printf("%d%c", P[i], " \n"[i + 1 == N]); }
  for (const auto &[l, r]: qs) { std::printf("%d %d\n", l, r); }

  return 0;
}
