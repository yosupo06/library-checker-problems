#include "../params.h"
#include "random.h"
#include <cstdio>
#include <set>
#include <utility>

using namespace std;

int main(int, char *argv[]) {

  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform<int>(N_MIN, 100);
  int m = gen.uniform<int>(M_MIN, 100);
  printf("%d %d\n", n, m);

  set<pair<int, int>> es;
  for (int i = 0; i < m; i++) {
    int a = gen.uniform(0, n - 1);
    int b = gen.uniform(0, n - 1);
    while (a == b || es.count(minmax({a, b}))) {
      a = gen.uniform(0, n - 1);
      b = gen.uniform(0, n - 1);
    }
    es.emplace(minmax({a, b}));
    printf("%d %d\n", a, b);
  }
  return 0;
}
