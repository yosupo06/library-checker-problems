#include <cstdio>
#include "common.h"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  gen_and_out(gen, N_MAX, N_MAX, N_MAX);
  return 0;
}
