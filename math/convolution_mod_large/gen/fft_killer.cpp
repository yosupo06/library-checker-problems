#include <cstdio>

#include "../fastio.h"
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_AND_M_MAX;
  int m = N_AND_M_MAX;
  vector<int> a(n), b(m);
  constexpr int B = 1 << 15;
  for (int i = 0; i < n; i++) {
    int lw = gen.uniform(B - 1000, B - 1);
    int up = gen.uniform(MOD / B - 1000, MOD / B - 1);
    a[i] = up * B + lw;
  }
  for (int i = 0; i < m; i++) {
    int lw = gen.uniform(B - 1000, B - 1);
    int up = gen.uniform(MOD / B - 1000, MOD / B - 1);
    b[i] = up * B + lw;
  }

  wtn(n, ' ', m);
  wtv(a);
  wtv(b);
  return 0;
}
