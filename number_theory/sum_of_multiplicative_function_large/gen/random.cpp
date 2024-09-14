#include "random.h"

#include <cassert>
#include <iostream>
#include <vector>

#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  ll N = gen.uniform<ll>(1LL, N_MAX);
  int a = gen.uniform<int>(2, MOD - 1);
  int b = gen.uniform<int>(2, MOD - 1);
  printf("1\n");
  printf("%lld %d %d\n", N, a, b);
  return 0;
}
