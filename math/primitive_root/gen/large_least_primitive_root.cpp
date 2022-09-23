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

// https://arxiv.org/pdf/2206.14193.pdf
int main() {
  int Q = MAX_Q;
  vector<ll> P;
  while (int(P.size()) < Q) {
    ll p = 6525032504501281;
    P.emplace_back(p);
  }

  printf("%d\n", Q);
  for (auto x: P) { printf("%lld\n", x); }
  return 0;
}
