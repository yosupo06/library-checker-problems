#include <cstdio>
#include <algorithm>
#include "random.h"
#include "../params.h"

using namespace std;

struct E {
  int U, V, W;
};

int main(int, char *argv[]) {
  int64_t seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int M = M_MAX;

  vector<E> E;
  for(int i = 1; i < N; i++)
    E.push_back({gen.uniform(0, i - 1), i, (int)gen.uniform(max(W_MAX - 100, W_MIN), W_MAX)});
  for(int i = N - 1; i < M; i++) {
    int Ui = gen.uniform(0, N - 1);
    int Vi = gen.uniform(0, N - 1);
    int Wi = gen.uniform(max(W_MAX - 100, W_MIN), W_MAX);
    E.push_back({Ui, Vi, Wi});
  }

  int K = min(N, (int)K_MAX);
  vector<int> X = gen.perm<int>(N);
  X.resize(K);

  auto f = gen.perm<int>(N);
  for(auto &e : E)
    e.U = f[e.U], e.V = f[e.V];
  for(int &x : X)
    x = f[x];
  sort(X.begin(), X.end());

  printf("%d %d\n", N, M);
  for(auto e : E)
    printf("%d %d %d\n", e.U, e.V, e.W);
  printf("%d\n", K);
  for(int i = 0; i < K; i++) {
    printf("%d", X[i]);
    if (i + 1 < K) printf(" ");
    else printf("\n");
  }

  return 0;
}
