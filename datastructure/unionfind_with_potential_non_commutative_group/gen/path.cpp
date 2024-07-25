#include "random.h"
#include "../params.h"
#include "../sol/acl.h"
#include <array>
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
using matrix = array<array<mint, 2>, 2>;

matrix id() {
  matrix M;
  M[0][0] = M[1][1] = 1, M[0][1] = M[1][0] = 0;
  return M;
}

matrix op(const matrix &A, const matrix &B) {
  matrix C;
  for(int i : {0, 1})
    for(int k : {0, 1})
      for(int j : {0, 1})
        C[i][j] += A[i][k] * B[k][j];
  return C;
}

matrix inv(const matrix &A) {
  matrix M = A;
  swap(M[0][0], M[1][1]);
  M[0][1] *= -1, M[1][0] *= -1;
  return M;
}

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

  auto random_matrix = [&gen]() {
    matrix M;
    while(M[0][0] * M[1][1] - M[0][1] * M[1][0] != 1) {
      for(int i : {0, 1}) for(int j : {0, 1})
        M[i][j] = gen.uniform(0ll, MOD - 1);
      int k = gen.uniform(0, 3);
      if (k == 0 and M[1][1] != 0) 
        M[0][0] = (M[0][1] * M[1][0] + 1) / M[1][1];
      if (k == 1 and M[1][0] != 0)
        M[0][1] = (M[0][0] * M[1][1] - 1) / M[1][0];
      if (k == 2 and M[0][1] != 0)
        M[1][0] = (M[0][0] * M[1][1] - 1) / M[0][1];
      if (k == 3 and M[0][0] != 0)
        M[1][1] = (M[0][1] * M[1][0] + 1) / M[0][0];
    }

    return M;
  };

  vector<matrix> A(N_AND_Q);
  for(int i = 0; i < N_AND_Q; i++)
    A[i] = random_matrix();

  std::vector<int> p(N_AND_Q);
  std::iota(p.begin(), p.end(), 0);
  gen.shuffle(p.begin(), p.end());
  std::printf("%d %d\n", N_AND_Q, N_AND_Q);
  for (const auto &[t, u, v] : qs) {
    if (t == 1) {
      std::printf("%d %d %d\n", t, p[u], p[v]);
    } else {
      matrix M;
      if (gen.uniform_bool())
        M = random_matrix();
      else
        M = op(inv(A[v]), A[u]);
      std::printf("%d %d %d %d %d %d %d\n", t, p[u], p[v], M[0][0].val(), M[0][1].val(), M[1][0].val(), M[1][1].val());
    }
  }

  return 0;
}
