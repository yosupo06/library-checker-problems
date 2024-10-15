#include <cstdio>
#include "../params.h"
#include "random.h"
#include <vector>

#include "common.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int X = 1 << 18;
  int a = X - 1, b = X, c = X + 1;
  int ns[] = {a, a, a, b, b, b, c, c, c};
  int ms[] = {a, b, c, a, b, c, a, b, c};

  int n = ns[seed % 9];
  int m = ms[seed % 9];

  int LIM_1 = A_MAX / n * 3;

  vector<ll> A = rand_gen(gen, n, -LIM_1, +LIM_1);
  vector<ll> B = rand_B(gen, m);
  upside_down(A);
  out(A, B);

  return 0;
}
