#include <array>
#include <iostream>
#include "random.h"
#include "../sol/acl.h"
#include "../params.h"

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

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

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

    int n = gen.uniform<int>(1, N_MAX);
    int q = Q_MAX;

    vector<matrix> A(n);
    for(int i = 0; i < n; i++)
      A[i] = random_matrix();

    printf("%d %d\n", n, q);
    for (int i = 0; i < q; i++) {
        int ty = gen.uniform_bool();
        int a = gen.uniform(0, n - 1);
        int b = gen.uniform(0, n - 1);
        if (ty == 1) {
          printf("%d %d %d\n", ty, a, b);
        } else {
          matrix M;
          if (gen.uniform_bool())
            M = random_matrix();
          else
            M = op(inv(A[b]), A[a]);
          printf("%d %d %d %d %d %d %d\n", ty, a, b, M[0][0].val(), M[0][1].val(), M[1][0].val(), M[1][1].val());
        }
    }
    return 0;
}
