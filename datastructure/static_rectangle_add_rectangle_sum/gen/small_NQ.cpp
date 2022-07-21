#include <iostream>
#include <tuple>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  ll N = 100;
  ll Q = 100;
  
  auto random_rect = [&]() -> tuple<ll, ll, ll, ll> {
    auto [l, r] = gen.uniform_pair<ll>(X_MIN, X_MAX);
    auto [d, u] = gen.uniform_pair<ll>(Y_MIN, Y_MAX);
    return {l, d, r, u};
  };

  printf("%lld %lld\n", N, Q);

  for (int n = 0; n < N; ++n) {
    auto [l, d, r, u] = random_rect();
    ll w = gen.uniform<ll>(0, MOD - 1);
    printf("%lld %lld %lld %lld %lld\n", l, d, r, u, w);
  }

  for (int q = 0; q < Q; ++q) {
    auto [l, d, r, u] = random_rect();
    printf("%lld %lld %lld %lld\n", l, d, r, u);
  }
  return 0;
}
