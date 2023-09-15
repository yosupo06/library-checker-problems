#include <iostream>
#include <vector>
#include <tuple>

#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;

#include "../gaussian.hpp"

using G = Gaussian_Integer<ll>;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  ll LIM1 = 1000;
  ll LIM2 = 1000000 / 2;

  auto gen_gauss = [&](ll LIM) -> G {
    ll x = gen.uniform<int>(-LIM, LIM);
    ll y = gen.uniform<int>(-LIM, LIM);
    return G{x, y};
  };

  int T = T_MAX;
  printf("%d\n", T);
  for (int t = 0; t < T; ++t) {
    G g = gen_gauss(LIM2);
    G a = gen_gauss(LIM1);
    G b = gen_gauss(LIM1);
    a *= g, b *= g;
    printf("%lld %lld %lld %lld\n", a.x, a.y, b.x, b.y);
  }
  return 0;
}
