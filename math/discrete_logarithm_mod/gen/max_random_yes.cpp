#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int mod_pow(ll a, ll n, int mod) {
  assert(0 <= a && a < mod && 0 <= n);
  ll r = 1;
  while (n) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod, n >>= 1;
  }
  return r;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = 100;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    int x, y, m;
    m = gen.uniform(800'000'000, 1'000'000'000);
    x = gen.uniform(0, m - 1);
    // y = gen.uniform(0, m - 1);
    int n = gen.uniform<int>(0, m);
    y = mod_pow(x, n, m);
    printf("%d %d %d\n", x, y, m);
  }
  return 0;
}
