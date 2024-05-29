#include "random.h"
#include <iostream>

using namespace std;
using ll = long long;

int lowbit(int x) { return (x == 0 ? -1 : __builtin_ctz(x)); }

int mod_pow(ll a, ll n, int mod) {
  assert(0 <= a && a < mod && 0 <= n);
  ll r = 1;
  while (n) {
    if (n & 1) r = r * a % mod;
    a = a * a % mod, n >>= 1;
  }
  return r;
}

bool primetest(int p) {
  if (p == 2 or p == 3 or p == 5 or p == 7) return true;
  if (p % 2 == 0 or p % 3 == 0 or p % 5 == 0 or p % 7 == 0) return false;
  if (p < 121) return p > 1;
  const int d = (p - 1) >> lowbit(p - 1);

  auto ok = [&](int a) -> bool {
    ll y = mod_pow(a, d, p);
    int t = d;
    while (y != 1 && y != p - 1 && t != p - 1) y = y * y % p, t <<= 1;
    if (y != p - 1 && t % 2 == 0) return false;
    return true;
  };
  for (int a: {2, 7, 61})
    if (!ok(a)) return false;
  return true;
}

int random_prime(Random& gen, int L, int R, bool safe) {
  if (!safe) {
    while (1) {
      int p = gen.uniform<int>(L, R);
      if (primetest(p)) return p;
    }
  }
  // L<=q=2p+1<=R
  while (1) {
    int p = random_prime(gen, L / 2, (R - 1) / 2, false);
    int q = 2 * p + 1;
    if (L <= q && q <= R && primetest(q)) return q;
  }
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int t = 100;
  printf("%d\n", t);
  for (int i = 0; i < t; i++) {
    int x, y, m;
    m = random_prime(gen, 800'000'000, 1'000'000'000, seed % 2);
    x = gen.uniform(0, m - 1);
    y = gen.uniform(0, m - 1);
    printf("%d %d %d\n", x, y, m);
  }
  return 0;
}
