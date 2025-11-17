#include <cstdio> // printf
#include <cstdlib> // atoll
#include "random.h"
#include "../params.h"

using namespace std;
using ll = long long;

int main(int, char* argv[]) {
  ll seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = T_MAX;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    ll n = gen.uniform<ll>(NM_MIN, 1000);
    ll m = gen.uniform<ll>(NM_MIN, NM_MAX);
    ll a = gen.uniform<ll>(AB_MIN, AB_MAX);
    ll b = gen.uniform<ll>(AB_MIN, AB_MAX);
    ll c = gen.uniform<ll>(0, m - 1);
    ll d = gen.uniform<ll>(0, m - 1);
    printf("%lld %lld %lld %lld %lld %lld\n", n, m, a, b, c, d);
  }
  return 0;
}
