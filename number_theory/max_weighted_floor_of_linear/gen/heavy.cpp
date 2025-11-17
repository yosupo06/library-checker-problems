#include <cassert> // assert
#include <cstdio> // printf
#include <cstdlib> // atoll
#include <limits> // numeric_limits
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;
using ull = unsigned long long;

int main(int, char* argv[]) {
  ll seed = atoll(argv[1]);
  auto gen = Random(seed);
  int t = T_MAX;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    ll n = NM_MAX;
    // generate large coefficients (a, b),(c, m),(e, f) using continued fraction expansions
    ll f = 1, e = 0, m = 0, c = 1, b = 1, a = 0;
    while (true) {
      // generate p using the number of trailing bits in a random 64-bit integer
      ll p = 1;
      ull r = gen.uniform<ull>(0, numeric_limits<ull>::max());
      while ((r & 3) == 3) {
        r >>= 2;
        p += 1;
      }
      a = c;
      b = m;
      c = e;
      m = f;
      f = m * p + b;
      e = c * p + a;
      if (f > NM_MAX || e >= NM_MAX) {
        break;
      }
    }
    // now (a, b),(c, m) are large enough
    // generate d
    ll d = gen.uniform<ll>(0, m - 1);
    // randomly negate a or b
    if (gen.uniform<int>(0, 1)) {
      a = -a;
    } else {
      b = -b;
    }
    // assert constraints
    assert(NM_MIN <= n && n <= NM_MAX);
    assert(NM_MIN <= m && m <= NM_MAX);
    assert(AB_MIN <= a && a <= AB_MAX);
    assert(AB_MIN <= b && b <= AB_MAX);
    assert(0 <= c && c < m);
    assert(0 <= d && d < m);
    printf("%lld %lld %lld %lld %lld %lld\n", n, m, a, b, c, d);
  }

  return 0;
}
