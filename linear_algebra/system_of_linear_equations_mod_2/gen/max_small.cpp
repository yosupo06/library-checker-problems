#include <iostream>
#include "random.h"
#include "../params.h"
#include "base.hpp"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int n = N_MAX;
  int m = gen.uniform<int>(2, 10);
  int r = gen.uniform<int>(1, min(n, m) - 1);
  if (seed % 2 == 0) gen_yes(n, m, r, gen);
  if (seed % 2 == 1) gen_no(n, m, r, gen);
  return 0;
}
