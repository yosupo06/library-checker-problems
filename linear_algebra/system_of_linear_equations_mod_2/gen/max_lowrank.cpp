#include <iostream>
#include "random.h"
#include "../params.h"
#include "base.hpp"

using namespace std;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int rs[] = {1, 10, 100, 1000, 4000};

  int n = N_MAX;
  int m = M_MAX;
  int r = rs[seed % 5];
  if (seed % 2 == 0) gen_yes(n, m, r, gen);
  if (seed % 2 == 1) gen_no(n, m, r, gen);
  return 0;
}
