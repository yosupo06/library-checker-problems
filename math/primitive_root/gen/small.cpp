#include <iostream>
#include "random.h"
#include "../params.h"

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
#include "../hpp/primetest.hpp"
#include "../hpp/factor.hpp"

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);

  int Q = MAX_Q;
  vector<ll> primes;
  ll p = 2;
  while (int(primes.size()) < 3 * Q) {
    if (primetest(p)) primes.emplace_back(p);
    ++p;
  }

  vector<long long> a(Q);
  for (int q = 0; q < Q; ++q) { a[q] = primes[3 * q + (seed % 3)]; }

  printf("%d\n", Q);
  for (auto x: a) { printf("%lld\n", x); }
  return 0;
}
