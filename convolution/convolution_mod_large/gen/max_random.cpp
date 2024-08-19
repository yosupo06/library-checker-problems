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

  for (int i = 0; i < n; i++) {
    a[i] = gen.uniform(0ll, MOD - 1);
  }
  for (int i = 0; i < m; i++) {
    b[i] = gen.uniform(0ll, MOD - 1);
  }

  wtn(n, ' ', m);
  wtv(a);
  wtv(b);
  return 0;
}
