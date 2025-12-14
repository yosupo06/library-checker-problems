#include <stdio.h>
#include "../params.h"
#include "random.h"

using namespace std;

int main(int, char* argv[]) {
  const long long seed = atoll(argv[1]);
  auto rng = Random(seed);

  int ns[] = {100, 1000};
  int n = ns[seed & 1];
  int m = N_AND_M_MAX;
  if (seed & 2) swap(n, m);

  printf("%d %d\n", n, m);
  for (int i = 0; i < n; ++i) {
    if (i > 0) printf(" ");
    printf("%llu", rng.uniform(0ULL, ~0ULL));
  }
  puts("");
  for (int i = 0; i < m; ++i) {
    if (i > 0) printf(" ");
    printf("%llu", rng.uniform(0ULL, ~0ULL));
  }
  puts("");
  return 0;
}
