// generate queries randomly

#include <cstdio>
#include <vector>

using namespace std;

#include "../params.h"
#include "random.h"

struct QueryData {
  int N, Q;
  vector<int> cmd, I, X, Y;

  QueryData(int _n, int _q, Random& gen) : N(_n), Q(_q), cmd(Q), I(Q), X(Q), Y(Q, -1) {
    for (int i = 0; i < Q; i++) {
      cmd[i] = gen.uniform(0, 1);
      if (N == 1) cmd[i] = 0;
      if (cmd[i] == 0) {
        I[i] = gen.uniform(0, N - 1);
        X[i] = gen.uniform(A_MIN, MOD - 1);
      } else {
        I[i] = gen.uniform(0, N - 2);
        X[i] = gen.uniform(B_MIN, MOD - 1);
        Y[i] = gen.uniform(C_MIN, MOD - 1);
      }
    }
  }

  void print() {
    for (int i = 0; i < Q; i++) {
      if (cmd[i] == 0) {
        printf("%d %d %d\n", cmd[i], I[i], X[i]);
      } else {
        printf("%d %d %d %d\n", cmd[i], I[i], X[i], Y[i]);
      }
    }
  }
};

struct QueryData_degree {
  int N, Q;
  vector<int> cmd, I, X, Y;

  QueryData_degree(int _n, int _q, Random& gen, vector<int> deg) : N(_n), Q(_q), cmd(Q), I(Q), X(Q), Y(Q, -1) {
    vector<int> S;
    for (int i = 0; i < N; ++i) {
      for (int cnt = 0; cnt < deg[i]; ++cnt) S.emplace_back(i);
    }
    if (S.empty()) S.emplace_back(0);
    auto random_S = [&]() -> int {
      int idx = gen.uniform(0, int(S.size()) - 1);
      return S[idx];
    };

    for (int i = 0; i < Q; i++) {
      cmd[i] = gen.uniform(0, 1);
      if (N == 1) cmd[i] = 0;
      if (cmd[i] == 0) {
        I[i] = random_S();
        X[i] = gen.uniform(A_MIN, MOD - 1);
      } else {
        I[i] = gen.uniform(0, N - 2);
        X[i] = gen.uniform(B_MIN, MOD - 1);
        Y[i] = gen.uniform(C_MIN, MOD - 1);
      }
    }
  }

  void print() {
    for (int i = 0; i < Q; i++) {
      if (cmd[i] == 0) {
        printf("%d %d %d\n", cmd[i], I[i], X[i]);
      } else {
        printf("%d %d %d %d\n", cmd[i], I[i], X[i], Y[i]);
      }
    }
  }
};
