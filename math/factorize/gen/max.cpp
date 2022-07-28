#include <stdio.h>
#include <stdlib.h>
#include "../params.h"

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  printf("%lld\n", MAX_Q);
  for (int i = 0; i < MAX_Q; ++i) {
    const long long a = MAX_A - seed * MAX_Q - i;
    printf("%lld\n", a);
  }
  return 0;
}
