#include <iostream>
#include "random.h"

#include "common.hpp"

using namespace std;
using ll = long long;

ll pow_mod(ll x, ll n, ll mod) {
  ll res = 1;
  while (n) {
    if (n & 1) res = res * x % mod;
    x = x * x % mod;
    n /= 2;
  }
  return res;
}

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = gen.uniform<int>(1, MAX_N);
  while ((MOD - 1) % N != 0) --N;

  int root = 3; // primitive root modulo 998244353

  int a = gen.uniform<int>(1, MOD - 1);
  int r = pow_mod(root, (MOD - 1) / N, MOD);

  assert(pow_mod(r, N, MOD) == 1);

  vector<int> y = make_y(gen, N);
  output(N, a, r, y);

  return 0;
}
