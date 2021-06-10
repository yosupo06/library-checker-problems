#include "random.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <utility>
#include <vector>

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  const int N = 200000;
  const int Q = 200000;

  assert(N == Q);

  struct query_type {
    int t;
    int u;
    int v;
  };

  std::vector<query_type> qs(Q);

  // unused-but-set-variable が誤反応するようなので、抑制する
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
  if (seed == 0 || seed == 1) {
    // parent[v] = u 最悪ケース
    const int K = 2 * N / 3;
    for (int i = 0; i != K; i += 1) {
      auto &[t, u, v] = qs[i];
      t = 0;
      u = i + 1;
      v = 0;
    }
    for (int i = K; i != Q; i += 1) {
      auto &[t, u, v] = qs[i];
      t = 1;
      u = 0;
      v = 1;
    }
  }
  if (seed == 2 || seed == 3) {
    // parent[v] = u 深さ最大
    for (int i = 0; i != Q - 1; i += 1) {
      auto &[t, u, v] = qs[i];
      t = 0;
      u = i + 1;
      v = i;
    }
    {
      auto &[t, u, v] = qs[Q - 1];
      t = 0;
      u = 0;
      v = Q - 1;
    }
  }
  if (seed == 1 || seed == 3) {
    // u, v 反転
    for (auto &query : qs) {
      std::swap(query.u, query.v);
    }
  }
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#pragma GCC diagnostic pop
#endif

  std::vector<int> p(N);
  std::iota(p.begin(), p.end(), 0);
  gen.shuffle(p.begin(), p.end());
  std::printf("%d %d\n", N, Q);
  for (const auto &[t, u, v] : qs) {
    std::printf("%d %d %d\n", t, p[u], p[v]);
  }

  return 0;
}
