#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <vector>
#include <algorithm>
using namespace std;

bool is_prime(int n) {
  if (n < 2) return false;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) return false;
  }
  return true;
}

long long modpow(long long a, long long p, long long m) {
  long long r = 1 % m;
  while (p) {
    if (p & 1) r = 1LL * r * a % m;
    a = 1LL * a * a % m;
    p >>= 1;
  }
  return r;
}
long long N_MAX = 10000000;
long long fac[10000000 + 1], ifac[10000000 + 1];

void build(long long m) {
  fac[0] = ifac[0] = fac[1] = ifac[1] = 1;
  long long N = std::min(m, N_MAX);
  for (int i = 2; i < N; ++i) {
    fac[i] = 1LL * fac[i - 1] * i % m;
  }
  ifac[N - 1] = modpow(fac[N - 1], m - 2, m);
  for (int i = N - 2; i > 1; --i) {
    ifac[i] = 1LL * ifac[i + 1] * (i + 1) % m;
  }
}

int main() {
  long long t, m;
  scanf("%lld %lld\n", &t, &m);
  build(m);

  while (t--) {
    long long n, k;
    scanf("%lld %lld\n", &n, &k);
    if(n < k){
      printf("0\n");
    }
    else{
      long long ans = ((fac[n] * ifac[k]) % m) * ifac[n - k] % m;
      printf("%lld\n", ans);
    }
  }
}
