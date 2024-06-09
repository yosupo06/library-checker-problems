#include <cstdio>
#include <cstdlib>

#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = min(L_MAX, R_MAX) / 6;
  // m = 16n-7<=M_MAX
  n = min<int>(n, (M_MAX + 7) / 16);
  vector<pair<int, int>> edge;
  for (int i = 0; i < 4 * n - 2; ++i) edge.emplace_back(i, i);
  for (int i = 0; i < 2 * n - 1; ++i) {
    edge.emplace_back(2 * i + 2, 2 * i + 0);
    edge.emplace_back(2 * i + 2, 2 * i + 1);
    edge.emplace_back(2 * i + 3, 2 * i + 0);
    edge.emplace_back(2 * i + 3, 2 * i + 1);
  }
  for (int i = 2 * n; i < 3 * n; ++i) {
    edge.emplace_back(2 * i + 0, 2 * i - 1);
    edge.emplace_back(2 * i + 0, 2 * i - 2);
    if (i < 3 * n - 1) edge.emplace_back(2 * i + 1, 2 * i + 0);
    edge.emplace_back(2 * i + 1, 2 * i - 1);
  }

  int m = int(edge.size());
  int L = 6 * n, R = 6 * n - 2;

  if (seed % 2 == 1) {
    // swap LR
    swap(L, R);
    for (auto& [a, b]: edge) { swap(a, b); }
  }

  if (seed % 3 == 1) { reverse(edge.begin(), edge.end()); }
  if (seed % 3 == 2) { gen.shuffle(edge.begin(), edge.end()); }

  printf("%d %d %d\n", L, R, m);
  for (auto [a, b]: edge) { printf("%d %d\n", a, b); }
  return 0;
}