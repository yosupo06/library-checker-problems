#include "random.h"
#include "../params.h"
#include "../sol/acl.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <numeric>
#include <utility>
#include <vector>
#include <algorithm>

using namespace std;
using namespace atcoder;

using mint = modint998244353;

mint id() { return 0; }
mint op(const mint &a, const mint &b) { return a + b; }
mint inv(const mint &a) { return -a; }

int main(int, char *argv[]) {
  const long long seed = std::atoll(argv[1]);
  Random gen(seed);

  const int N_AND_Q = std::min(N_MAX, Q_MAX);

  struct query_type {
    int t;
    int u;
    int v;
  };

  std::vector<query_type> qs(N_AND_Q);

  // unused-but-set-variable が誤反応するようなので、抑制する
#if defined(__GNUC__) && !defined(__llvm__) && !defined(__INTEL_COMPILER)
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
  if (seed == 0 || seed == 1) {
    // parent[v] = u 最悪ケース
    const int K = 2 * N_AND_Q / 3;
    for (int i = 0; i != K; i += 1) {
      auto &[t, u, v] = qs[i];
      t = 0;
      u = i + 1;
      v = 0;
    }
    for (int i = K; i != N_AND_Q; i += 1) {
      auto &[t, u, v] = qs[i];
      t = 1;
      u = 0;
      v = 1;
    }
  }
  if (seed == 2 || seed == 3) {
    // parent[v] = u 深さ最大
    for (int i = 0; i != N_AND_Q - 1; i += 1) {
      auto &[t, u, v] = qs[i];
      t = 0;
      u = i + 1;
      v = i;
    }
    {
      auto &[t, u, v] = qs[N_AND_Q - 1];
      t = 0;
      u = 0;
      v = N_AND_Q - 1;
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

  vector<mint> A(N_AND_Q);
  for(mint &x : A)
    x = gen.uniform<int>(0, MOD - 1);

  std::vector<int> p(N_AND_Q);
  std::iota(p.begin(), p.end(), 0);
  gen.shuffle(p.begin(), p.end());
  std::printf("%d %d\n", N_AND_Q, N_AND_Q);
  for (const auto &[t, u, v] : qs) {
    if (t == 1) {
      std::printf("%d %d %d\n", t, p[u], p[v]);
    } else {
      mint x;
      if (gen.uniform_bool())
        x = gen.uniform<int>(0, MOD - 1);
      else
        x = op(inv(A[v]), A[u]);
      std::printf("%d %d %d %d\n", t, p[u], p[v], x.val());
    }
  }

  return 0;
}
