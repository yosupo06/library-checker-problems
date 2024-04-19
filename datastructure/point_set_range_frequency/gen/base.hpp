#include <cassert>
#include <cstdio>
#include <set>
#include <vector>

#include "../params.h"
#include "random.h"

// p = prob(query type 0)
void generate(Random &gen, const int N, const int Q, const int K,
              const double p) {
  std::printf("%d %d\n", N, Q);

  std::vector<int> S;
  std::set<int> s;
  for (int i = 0; i < K; i++) {
    while (true) {
      const int a = gen.uniform(A_MIN, A_MAX);
      if (!s.count(a)) {
        s.insert(a);
        S.push_back(a);
        break;
      }
    }
  }

  auto random_x = [&]() -> int { return S[gen.uniform(0, K - 1)]; };

  for (int i = 0; i < N; i++) {
    if (i != 0) { std::printf(" "); }
    std::printf("%d", random_x());
  }
  std::printf("\n");

  for (int i = 0; i < Q; i++) {
    int t = (gen.uniform01() < p ? 0 : 1);
    if (N == 0) t = 1;
    if (t == 0) {
      int k = gen.uniform<int>(0, N - 1);
      int x = random_x();
      printf("%d %d %d\n", t, k, x);
    }
    if (t == 1) {
      auto [l, r] = gen.uniform_pair(0, N + 1);
      r -= 1;
      int x = random_x();
      printf("%d %d %d %d\n", t, l, r, x);
    }
  }
}
