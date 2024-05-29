#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(MIN_N, MAX_N);
  int m = gen.uniform<int>(0, MAX_M);

  using P = pair<int, int>;
  vector<P> edges;
  for (int i = 0; i < m; ++i) {
    while (1) {
      int a = gen.uniform<int>(0, n - 1);
      int b = gen.uniform<int>(0, n - 1);

      if (seed % 2 == 0 && a == b) continue;

      edges.push_back({a, b});
      break;
    }
  }

  printf("%d %d\n", n, m);
  for (int i = 0; i < m; i++) {
    printf("%d %d\n", edges[i].first, edges[i].second);
  }
  return 0;
}