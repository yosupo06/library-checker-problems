#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<pair<int, int>> out;

  int ns[] = {100, 1000, N_MAX};

  int t = 1;
  int n = ns[seed % 3];
  int m = M_MAX;
  vector<pair<int, int>> edges;
  int v = gen.uniform<int>(0, n - 1);
  for (int i = 0; i < m; ++i) {
    int w = gen.uniform<int>(0, n - 1);
    int a = v, b = w;
    if (gen.uniform<int>(0, 1)) swap(a, b);
    edges.emplace_back(a, b);
    v = w;
  }
  gen.shuffle(edges.begin(), edges.end());
  out.emplace_back(n, m);
  for (auto& [a, b]: edges) out.emplace_back(a, b);

  printf("%d\n", t);
  for (auto [a, b]: out) printf("%d %d\n", a, b);
  return 0;
}
