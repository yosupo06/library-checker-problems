#include "../params.h"
#include "random.h"
#include <set>

using namespace std;

int main(int, char **argv) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = gen.uniform(0, 2) == 0 ? N_MAX : (gen.uniform(0, 1) == 0 ? 10 : 1000);
  int m = M_MAX;
  printf("%d %d\n", n, m);

  set<int> s;
  for (int i = 0; i < m; i++) {
    int u, v, w;
    do {
      u = gen.uniform(0ll, (long long)n - 1);
      v = gen.uniform(0ll, (long long)n - 1);
      w = gen.uniform(1ll, W_MAX);
    } while (s.find(w) != s.end());
    s.insert(w);
    printf("%d %d %d\n", u, v, w);
  }

  return 0;
}
