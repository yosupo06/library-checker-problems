#include <stdio.h>
#include "../params.h"

int main() {
  const int T = T_FEW;
  printf("%d\n", T);
  int t = 0;
  for (unsigned long long s = 0; ; ++s) {
    for (unsigned long long a = 0; a <= s; ++a) {
      const unsigned long long b = s - a;
      printf("%llu %llu\n", ~0ULL - a, ~0ULL - b);
      if (++t >= T) {
        return 0;
      }
    }
  }
  return 0;
}
