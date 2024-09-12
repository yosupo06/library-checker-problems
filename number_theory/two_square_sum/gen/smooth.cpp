#include <iostream>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  vector<ll> primes;
  if (seed == 0) { primes = {2, 3, 5, 7, 11, 13, 17}; }
  if (seed == 1) { primes = {2, 3 * 3, 5, 7 * 7, 11 * 11, 13, 17}; }
  if (seed == 2) { primes = {2, 5, 13, 17, 29}; }
  if (seed == 3) { primes = {5, 13, 17, 29, 37, 41}; }
  if (seed == 4) { primes = {5, 13, 17}; }

  auto F = [&]() -> ll {
    ll x = 1;
    while (x <= MAX_A / primes[0]) {
      ll k = gen.uniform<int>(0, (primes.size()) - 1);
      ll p = primes[k];
      if (p > MAX_A / x) continue;
      x *= p;
    }
    return x;
  };

  int Q = MAX_Q;
  printf("%d\n", Q);
  for (int i = 0; i < Q; i++) { printf("%lld\n", F()); }
}
