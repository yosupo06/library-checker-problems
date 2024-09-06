#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int k = seed % 3 + 1;
  int n = N_MAX;
  assert(k <= n);

  vector<pair<int, int>> out;
  vector<int> S = gen.choice(k, 0, n - 1);

  int t = 1;
  int m = M_MAX;
  vector<pair<int, int>> edges;
  int v = gen.uniform<int>(0, n - 1);
  for (int i = 0; i < m; ++i) {
    // 確率 1/2 で S を通るようにする
    int w = gen.uniform<int>(0, n - 1);
    if (gen.uniform<int>(0, 1)) { w = S[gen.uniform<int>(0, k - 1)]; }
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
