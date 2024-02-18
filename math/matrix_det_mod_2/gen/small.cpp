#include "random.h"
#include "../params.h"
#include "../base.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int ns[] = {1, 1, 2, 2, 3, 3};
  int ans = seed % 2;
  int n = ns[seed % 6];
  gen_and_out(gen, n, ans);
  return 0;
}
