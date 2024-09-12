#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char **argv) {
  const long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int primes[] = {2, 3, 5, 13};
  ll p = primes[seed % 4];

  vector<ll> A = {1};
  while (1) {
    ll a = A.back();
    if (a > MAX_A / p) break;
    A.emplace_back(a * p);
  }

  printf("%lld\n", MAX_Q);
  for (int i = 0; i < MAX_Q; ++i) {
    ll k = gen.uniform<int>(0, A.size() - 1);
    ll a = A[k];
    printf("%lld\n", a);
  }
  return 0;
}
