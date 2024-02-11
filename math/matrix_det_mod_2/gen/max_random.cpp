#include "random.h"
#include "../params.h"
#include "../base.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int ans = seed % 2;
  int n = N_MAX;
  gen_and_out(gen, n, ans);
  return 0;
}
