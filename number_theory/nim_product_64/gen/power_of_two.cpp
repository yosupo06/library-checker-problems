#include <stdio.h>
#include "../params.h"

int main() {
  const int T = 64 * 64;
  printf("%d\n", T);
  for (int i = 0; i < 64; ++i) {
    for (int j = 0; j < 64; ++j) {
      printf("%llu %llu\n", 1ULL << i, 1ULL << j);
    }
  }
  return 0;
}
