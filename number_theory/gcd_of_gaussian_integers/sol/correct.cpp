#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;
using ll = long long;

#include "../gaussian.hpp"

using G = Gaussian_Integer<ll>;

int main() {
  int T;
  scanf("%d", &T);

  for (int t = 0; t < T; ++t) {
    ll a1, b1, a2, b2;
    scanf("%lld %lld %lld %lld", &a1, &b1, &a2, &b2);
    G a(a1, b1);
    G b(a2, b2);
    auto [g, x, y] = G::extgcd(a, b);
    assert(a * x + b * y == g);
    assert((g == G{0, 0} && a == G{0, 0}) || (a % g == 0));
    assert((g == G{0, 0} && b == G{0, 0}) || (b % g == 0));
    printf("%lld %lld\n", g.x, g.y);
  }

  return 0;
}
