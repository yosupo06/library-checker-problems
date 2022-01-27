#include <cstdio>
#include <vector>
#include <cassert>

using namespace std;
using ll = long long;

constexpr int MOD = 998'244'353;

void zeta(vector<ll>& a) {
  int n = a.size() - 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 2; j <= n / i; ++j) {
      a[i] += a[i * j];
      if (a[i] >= MOD) a[i] -= MOD;
    }
  }
}

void mobius(vector<ll>& a) {
  int n = a.size() - 1;
  for (int i = n; i >= 1; --i) {
    for (int j = 2; j <= n / i; ++j) {
      a[i] -= a[i * j];
      if (a[i] < 0) a[i] += MOD;
    }
  }
}

int main() {
  int n;
  scanf("%d", &n);

  vector<ll> a(n + 1), b(n + 1);
  for (int i = 1; i <= n; ++i) scanf("%lld", &a[i]);
  for (int i = 1; i <= n; ++i) scanf("%lld", &b[i]);

  zeta(a);
  zeta(b);
  vector<ll> c(n + 1);
  for (int i = 1; i <= n; ++i) c[i] = a[i] * b[i] % MOD;
  mobius(c);

  for (int i = 1; i <= n; ++i) {
    if (i > 1) printf(" ");
    printf("%lld", c[i]);
  }
  printf("\n");
  return 0;
}
