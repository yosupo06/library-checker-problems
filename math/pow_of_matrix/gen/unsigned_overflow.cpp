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
  int val = MOD - 2;

  // Find smallest size n where n * val * val > numeric_limits<unsigned long
  // long>::max()
  int n = 0;
  unsigned long long res = 0;
  long long val2 = (long long)val * val;
  while (res + val2 >= res) // Check if adding val2 to res will overflow
  {
    res += val2;
    ++n;
  }

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
