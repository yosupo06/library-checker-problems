/**
 *  n < 2048のときとmが素数の時に正しい答えを返すプログラム。
 */

#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
using namespace std;

#include "../params.h"

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

int modpow(int a, int p, int m) {
  int r = 1 % m;
  while (p) {
    if (p & 1) r = 1LL * r * a % m;
    a = 1LL * a * a % m;
    p >>= 1;
  }
  return r;
}

constexpr int table = 2048;
int dp[table][table];
int fac[M_MAX + 1], ifac[M_MAX + 1];

void build(int m) {
  fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
  for (int i = 2; i < m; ++i) {
    fac[i] = 1LL * fac[i - 1] * i % m;
  }
  ifac[m - 1] = modpow(fac[m - 1], m - 2, m);
  for (int i = m - 2; i > 1; --i) {
    ifac[i] = 1LL * ifac[i + 1] * (i + 1) % m;
  }
}

int small_binom(int n, int k, int m) {
  assert(n >= 0 || k >= 0 || n < m);
  if (n < k) return 0;
  return 1LL * fac[n] * ifac[k] % m * ifac[n - k] % m;
}

int Lucas(long long n, long long k, int m) {
  long long res = 1 % m;
  while (n) {
    res = res * small_binom(n % m, k % m, m) % m;
    n /= m, k /= m;
  }
  return res;
}

int main() {
  int t, m;
  scanf("%d %d\n", &t, &m);

  bool prime = is_prime(m);
  if (prime) {
    build(m);
  } else {
    for (int i = 0; i < table; i++) {
      for (int j = 0; j <= i; j++) {
        if (j == 0) {
          dp[i][j] = m == 1 ? 0 : 1;
        } else {
          if (i != 0) {
            dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
            if (dp[i][j] >= m) dp[i][j] -= m;
          }
        }
      }
    }
  }

  while (t--) {
    long long n, k;
    scanf("%lld %lld\n", &n, &k);
    if (prime) {
      printf("%d\n", Lucas(n, k, m));
    } else if (n < table) {
      printf("%d\n", dp[n][k]);
    } else if (m == 1) {
      printf("0\n");
    } else {
      exit(1);
    }
  }
}
