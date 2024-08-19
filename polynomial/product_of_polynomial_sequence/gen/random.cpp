#include <cstdio>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(1, N_MAX);
  int D = gen.uniform<int>(0, D_MAX);

  vector<int> deg(N);
  for (int d = 0; d < D; ++d) {
    int i = gen.uniform<int>(0, N - 1);
    deg[i]++;
  }

  auto gen_poly = [&](int d) -> vector<int> {
    vector<int> f(d + 1);
    for (int j = 0; j <= d; ++j) {
      int lo = 0;
      if (j == d) lo = 1;
      f[j] = gen.uniform<int>(lo, MOD - 1);
    }
    return f;
  };

  printf("%d\n", N);
  for (int i = 0; i < N; i++) {
    int d = deg[i];
    vector<int> f = gen_poly(d);
    printf("%d", d);
    for (int j = 0; j <= d; ++j) { printf(" %d", f[j]); }
    printf("\n");
  }
  return 0;
}
