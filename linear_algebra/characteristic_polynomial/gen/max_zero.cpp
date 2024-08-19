#include <cstdlib>
#include <cstdio>

#include "../params.h"

int main() {
  int n = N_MAX;

  std::printf("%d\n", n);

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      std::printf("0");
      if (j != n - 1) std::printf(" ");
    }
    std::printf("\n");
  }
  return 0;
}
