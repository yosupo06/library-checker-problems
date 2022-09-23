#include <iostream>
#include "random.h"

#include <vector>
#include <cassert>
using namespace std;
using ll = long long;
using pi = pair<ll, ll>;
#include "../hpp/primetest.hpp"
#include "../hpp/factor.hpp"
#include "../hpp/mod_pow.hpp"

ll solve(ll p) {
  ll r = 1;
  auto pf = factor(p - 1);
  while (1) {
    bool ok = 1;
    for (auto&& [q, k]: pf) {
      if (mod_pow_long(r, (p - 1) / q, p) == 1) {
        ok = 0;
        break;
      }
    }
    if (ok) break;
    ++r;
  }
  return r;
}

int main() {
  int Q;
  scanf("%d", &Q);

  for (int q = 0; q < Q; q++) {
    ll p;
    scanf("%lld", &p);
    ll ANS = solve(p);
    printf("%lld\n", ANS);
  }
  return 0;
}
