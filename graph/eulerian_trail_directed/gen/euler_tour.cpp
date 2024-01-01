#include <cstdio>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int tmp[] = {1, 2, 10, N_MAX};
  int d = tmp[seed % 4];

  int n = min(N_MAX, M_MAX / 2 + 1);
  int m = 2 * (n - 1);
  vector<pair<int, int>> edges;

  for (int v = 1; v < n; ++v) {
    int l = max(0, v - d), r = v - 1;
    int p = gen.uniform<int>(l, r);
    edges.emplace_back(p, v);
    edges.emplace_back(v, p);
  }

  gen.shuffle(edges.begin(), edges.end());
  vector<int> new_idx(n);
  for (int i = 0; i < n; ++i) new_idx[i] = i;
  gen.shuffle(new_idx.begin(), new_idx.end());
  for (auto& [a, b]: edges) { a = new_idx[a], b = new_idx[b]; }

  vector<pair<int, int>> out;
  out.emplace_back(n, m);
  for (auto& [a, b]: edges) out.emplace_back(a, b);

  int t = 1;
  printf("%d\n", t);
  for (auto [a, b]: out) printf("%d %d\n", a, b);
  return 0;
}
