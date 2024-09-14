#include <cassert>
#include <iostream>
#include <vector>

#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;

ll f(ll n) {
  ll ret = 1;
  while ((ret + 1) * (ret + 2) <= n) ++ret;
  return ret * (ret + 1);
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  ll N = gen.uniform<ll>(1000LL, N_MAX - 10L);
  ll d = seed % 3 - 1;
  printf("%lld\n", f(N) + d);
  return 0;
}
