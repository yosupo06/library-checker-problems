#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
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

  printf("%d %d\n", n, m);
  for (auto& [a, b]: edges) printf("%d %d\n", a, b);
  return 0;
}
