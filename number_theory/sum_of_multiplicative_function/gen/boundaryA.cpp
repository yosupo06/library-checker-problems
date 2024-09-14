#include <cassert>
#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;

ll f(ll n) {
  ll ret = 1;
  while ((ret + 1) * (ret + 1) <= n) ++ret;
  return ret * ret;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  ll N = gen.uniform<ll>(1000LL, N_MAX - 10L);
  ll d = seed % 5 - 2;
  int a = gen.uniform<int>(2, MOD - 1);
  int b = gen.uniform<int>(2, MOD - 1);

  printf("1\n");
  printf("%lld %d %d\n", f(N) + d, a, b);
  return 0;
}
