#include <cstdio>
#include <cstdlib>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int n = gen.uniform<int>(1, N - 1);
  int m = M_MAX;

  vector<pair<int, int>> edges;
  int v = gen.uniform<int>(0, n - 1);
  int s = v;
  for (int i = 0; i < m; ++i) {
    int w = gen.uniform<int>(0, n - 1);
    int a = v, b = w;
    // back to start
    if (i == m - 1) b = s;
    edges.emplace_back(a, b);
    v = w;
  }
  gen.shuffle(edges.begin(), edges.end());

  vector<int> S(N);
  for (int i = 0; i < N; ++i) S[i] = i;
  gen.shuffle(S.begin(), S.end());
  for (auto& [a, b]: edges) a = S[a], b = S[b];

  printf("%d %d\n", N, m);
  for (auto& [a, b]: edges) printf("%d %d\n", a, b);
  return 0;
}
