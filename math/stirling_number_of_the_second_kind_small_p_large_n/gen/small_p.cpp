#include <iostream>

#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;
bool is_prime(int p) {
  if (p <= 1) return false;
  for (int i = 2; i < p; ++i)
    if (p % i == 0) return false;
  return true;
}

// p が小さいケースは、答が 0 ばかりにならないように注意して作る
int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int primes[] = {2, 3, 5, 7, 11, 13};

  int T = T_MAX;
  int p = primes[seed % 6];
  printf("%d %d\n", T, p);

  auto nonzero_binom = [&]() -> pair<ll, ll> {
    ll a = gen.uniform<ll>(0, N_MAX / p);
    auto dfs = [&](auto& dfs, ll a) -> ll {
      if (a <= p) return gen.uniform<ll>(0, a);
      ll r = a % p;
      a /= p;
      ll b = dfs(dfs, a);
      return p * b + (gen.uniform<ll>(0, r));
    };
    ll b = dfs(dfs, a);
    return {a, b};
  };

  auto gen_nk = [&]() -> pair<ll, ll> {
    while (1) {
      auto [a, i] = nonzero_binom();
      ll b = gen.uniform<ll>(1, p - 1);
      ll j = gen.uniform<ll>(0, p);
      ll n = (p - 1) * a + i + b;
      ll k = i * p + j;
      if (0 <= k && k <= n && n <= N_MAX) return {n, k};
    }
  };

  for (int t = 0; t < T; ++t) {
    auto [n, k] = gen_nk();
    printf("%lld %lld\n", n, k);
  }
  return 0;
}
