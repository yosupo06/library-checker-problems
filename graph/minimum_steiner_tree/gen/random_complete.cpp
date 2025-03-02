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

  int N = (int)sqrt(2 * M_MAX);
  int M = N * (N - 1) / 2;

  vector<E> E;
  for(int Ui = 0; Ui < N; Ui++)
    for(int Vi = Ui + 1; Vi < N; Vi++)
      E.push_back({Ui, Vi, (int)gen.uniform(W_MIN, W_MAX)});

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
