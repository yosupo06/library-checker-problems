#include <iostream>
#include <vector>
#include <tuple>

#include "../params.h"
#include "random.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int T = T_MAX;
  printf("%d\n", T);
  for (int t = 0; t < T; ++t) {
    ll a = 1, b = 0, c = 0, d = 0;
    while (1) {
      int k = gen.uniform<int>(0, 3);
      for (int i = 0; i < k; ++i) { tie(a, b) = make_pair(b, -a); }
      ll aa = c + a, bb = d + b, cc = a, dd = b;
      if (min<ll>({aa, bb, cc, dd}) < MIN) break;
      if (max<ll>({aa, bb, cc, dd}) > MAX) break;
      a = aa, b = bb, c = cc, d = dd;
    }
    printf("%lld %lld %lld %lld\n", a, b, c, d);
  }
  return 0;
}
