#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <cstdlib>
#include <cstdio>

#include "../params.h"
#include "random.h"

using namespace std;

/*
要素の種類 K
0:1000, dense
1:1000, random
2:10^6, dense
3:10^6, random

クエリ
0:[1/6,1/6,1/6,1/6,1/6,1/6]
1:[1/5,eps,1/5,1/5,1/5,1/5]
2:[1,eps,eps,eps,eps,eps]
3:[eps,1,eps,eps,eps,eps]
4:[eps,eps,1,eps,eps,eps]
5:[eps,eps,eps,1,eps,eps]
6:[eps,eps,eps,eps,1,eps]
7:[eps,eps,eps,eps,eps,1]

seed/8, seed%8
*/

vector<int> gen_val(Random& gen, int seed) {
  seed /= 8;
  int K = ((seed == 0 || seed == 1) ? 1000 : 1000000);
  if (seed == 0 || seed == 2) {
    int s = gen.uniform<int>(0, A_MAX - K + 1);
    vector<int> A(K);
    for (int i = 0; i < K; ++i) A[i] = i + s;
    return A;
  }
  return gen.choice<int>(K, A_MIN, A_MAX);
}

vector<int> gen_prob(int seed) {
  seed %= 8;
  vector<int> S = {0, 1, 2, 3, 4, 5};
  for (int t = 0; t < 6; ++t) {
    bool add = 0;
    if (seed == 0) add = 1;
    if (seed == 1 && t != 1) add = 1;
    if (seed == 2 && t == 0) add = 1;
    if (seed == 3 && t == 1) add = 1;
    if (seed == 4 && t == 1) add = 1;
    if (seed == 5 && t == 1) add = 1;
    if (seed == 6 && t == 1) add = 1;
    if (seed == 7 && t == 1) add = 1;
    if (add) {
      for (int i = 0; i < 100; ++i) S.emplace_back(t);
    }
  }
  return S;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<int> kind = gen_val(gen, seed);
  vector<int> S = gen_prob(seed);

  vector<int> A;
  for (auto& x: kind) {
    if (gen.uniform<int>(0, 1)) { A.emplace_back(x); }
  }
  if (int(A.size()) > N_MAX) A.resize(N_MAX);

  int N = A.size();
  int Q = Q_MAX;

  printf("%d %d\n", N, Q);
  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    printf("%d", A[i]);
  }
  printf("\n");

  int sz = S.size();
  int K = kind.size();

  set<int> ANS(A.begin(), A.end());

  for (int i = 0; i < Q; i++) {
    int t = S[gen.uniform<int>(0, sz - 1)];
    int x;
    if (t == 0) {
      x = kind[gen.uniform<int>(0, K - 1)];
      ANS.insert(x);
    }
    if (t == 1) {
      x = kind[gen.uniform<int>(0, K - 1)];
      ANS.erase(x);
    }
    if (t == 2) {
      int n = ANS.size();
      x = gen.uniform<int>(1, n + 1);
      if (gen.uniform<int>(0, 100) == 0) { x = gen.uniform<int>(1, A_MAX); }
    }
    if (t == 3 || t == 4 || t == 5) {
      x = gen.uniform<int>(A_MIN, A_MAX);
      if (gen.uniform<int>(0, 1)) { x = kind[gen.uniform<int>(0, K - 1)]; }
    }

    printf("%d %d\n", t, x);
  }
  return 0;
}
