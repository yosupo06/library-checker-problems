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
  for (int i = 0; i < m; ++i) {
    int a = gen.uniform<int>(0, n - 1);
    int b = gen.uniform<int>(0, n - 1);
    edges.emplace_back(a, b);
  }

  printf("%d %d\n", n, m);
  for (auto& [a, b]: edges) printf("%d %d\n", a, b);
  return 0;
}
