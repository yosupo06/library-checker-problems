#include "random.h"
#include <iostream>
#include <vector>
#include <cassert>
#include "../params.h"

using namespace std;
using ll = long long;

ll f(ll n) {
  ll ret = 1;
  while((ret+1)*(ret+2)<=n)++ret;
  return ret*(ret+1);
}

int main(int, char* argv[]) {

    long long seed = atoll(argv[1]);
    auto gen = Random(seed);

    ll N = gen.uniform<ll>(10LL, N_MAX);
    printf("%lld\n", f(N));
    return 0;
}
