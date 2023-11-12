#include <iostream>
#include <set>
#include <limits>

#include "random.h"
#include "../params.h"

using namespace std;

using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int val = MOD / 2 - 1;
  unsigned long long max_ll = numeric_limits<long long>::max();

  // Find smallest size n where n * val * val > max_ll
  int n = 0;
  for (unsigned long long res = 0; res <= max_ll;
       res += (long long)val * val, ++n)
    ;
  ll K = gen.uniform<ll>(0, K_MAX);

  printf("%d %lld\n", n, K);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (j) printf(" ");
      printf("%d", val);
    }
    printf("\n");
  }
  return 0;
}
