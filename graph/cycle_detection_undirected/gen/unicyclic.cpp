#include <cstdio>
#include <vector>
#include <tuple>
#include <utility>
#include <algorithm>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto rnd = Random(seed);

  int N = rnd.uniform(N_MIN, N_MAX);
  int M = N;

  vector<int> V(N);
  for (int i = 0; i < N; ++i) V[i] = i;
  rnd.shuffle(V.begin(), V.end());

  vector<pair<int, int>> edges;
  for (int v = 1; v < N; ++v) {
    int u = rnd.uniform<int>(0, v - 1);
    edges.emplace_back(V[u], V[v]);
  }
  int u = rnd.uniform<int>(0, N - 1);
  int v = rnd.uniform<int>(0, N - 1);
  edges.emplace_back(u, v);

  rnd.shuffle(edges.begin(), edges.end());
  for (auto&& [a, b]: edges) {
    if (rnd.uniform<int>(0, 1)) std::swap(a, b);
  }

  printf("%d %d\n", N, M);
  for (auto&& [a, b]: edges) { printf("%d %d\n", a, b); }
  return 0;
}
