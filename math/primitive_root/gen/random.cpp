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
  vector<ll> P;
  while (int(P.size()) < Q) {
    ll p = gen.uniform<ll>(MIN_P, MAX_P);
    if (primetest(p)) P.emplace_back(p);
  }

  printf("%d\n", Q);
  for (auto x: P) { printf("%lld\n", x); }
  return 0;
}
