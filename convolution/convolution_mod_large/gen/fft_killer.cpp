#include <cstdio>

#include "../fastio.h"
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  auto sub = seed % 2 ? 1000 : 10;

  int n = N_AND_M_MAX;
  int m = N_AND_M_MAX;
  vector<int> a(n), b(m);
  constexpr int B = 1 << 15;
  for (int i = 0; i < n; i++) {
    int lw = gen.uniform(B - sub, B - 1);
    int up = gen.uniform(MOD / B - sub, MOD / B - 1);
    a[i] = up * B + lw;
  }
  for (int i = 0; i < m; i++) {
    int lw = gen.uniform(B - sub, B - 1);
    int up = gen.uniform(MOD / B - sub, MOD / B - 1);
    b[i] = up * B + lw;
  }

  wtn(n, ' ', m);
  wtv(a);
  wtv(b);
  return 0;
}
