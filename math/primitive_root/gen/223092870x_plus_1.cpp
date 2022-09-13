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
  auto gen = Random(seed);

  int Q = MAX_Q;

  ll C = 223092870;
  assert(C == 2LL * 3 * 5 * 7 * 11 * 13 * 17 * 19 * 23);
  ll LIM = MAX_P / C;

  vector<ll> P;
  while (int(P.size()) < Q) {
    ll x = gen.uniform<ll>(1, LIM);
    ll p = C * x + 1;
    if (primetest(p)) P.emplace_back(p);
  }

  printf("%d\n", Q);
  for (auto x: P) { printf("%lld\n", x); }
  return 0;
}
