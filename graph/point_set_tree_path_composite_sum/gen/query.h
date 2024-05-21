// generate queries randomly

#include <cstdio>
#include <vector>

using namespace std;

#include "../params.h"
#include "random.h"

struct QueryData {
  int N, Q;
  vector<int> cmd, I, X, Y, R;

  QueryData(int _n, int _q, Random& gen)
      : N(_n), Q(_q), cmd(Q), I(Q), X(Q), Y(Q, -1), R(Q) {
    for (int i = 0; i < Q; i++) {
      cmd[i] = gen.uniform(0, 1);
      if (N == 1) cmd[i] = 0;
      if (cmd[i] == 0) {
        I[i] = gen.uniform(0, N - 1);
        X[i] = gen.uniform(A_MIN, MOD - 1);
        R[i] = gen.uniform(0, N - 1);
      } else {
        I[i] = gen.uniform(0, N - 2);
        X[i] = gen.uniform(B_MIN, MOD - 1);
        Y[i] = gen.uniform(C_MIN, MOD - 1);
        R[i] = gen.uniform(0, N - 1);
      }
    }
  }

  void print() {
    for (int i = 0; i < Q; i++) {
      if (cmd[i] == 0) {
        printf("%d %d %d %d\n", cmd[i], I[i], X[i], R[i]);
      } else {
        printf("%d %d %d %d %d\n", cmd[i], I[i], X[i], Y[i], R[i]);
      }
    }
  }
};
