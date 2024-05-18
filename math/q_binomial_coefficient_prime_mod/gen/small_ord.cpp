#include <iostream>
#include <cassert>

#include "../params.h"
#include "random.h"

int mod_pow(int a, int n, int mod) {
  assert(n >= 0);
  assert(0 <= a && a < mod);
  int ans = 1;
  while (n) {
    if (n & 1) ans = static_cast<long long>(ans) * a % mod;
    a = static_cast<long long>(a) * a % mod, n >>= 1;
  }
  return ans;
}

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

/*
take small a
p=ab+1
q=pow(rand,b,p)
*/

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);
  int as[] = {2, 3, 5, 7, 11, 13};

  long long t = T_MAX;
  long long p, q;
  while (1) {
    int a = as[seed % 6];
    int mx = (M_MAX - 1) / a;
    int b = gen.uniform<int>(1, mx);
    p = a * b + 1;
    if (!is_prime(p)) continue;
    while (1) {
      int r = gen.uniform<int>(1, p - 1);
      q = mod_pow(r, b, p);
      if (q != 1) break;
    }
    break;
  }

  printf("%lld %lld %lld\n", t, p, q);

  while (t--) {
    long long n, k;
    n = gen.uniform<long long>(0, std::min(p, N_MAX) - 1);
    k = gen.uniform<long long>(0, std::min(p, N_MAX) - 1);
    printf("%lld %lld\n", n, k);
  }

  return 0;
}
