#include <cassert>
#include <cstdio>
#include <vector>

using namespace std;
using ll = long long;
const int mod = 998244353;

int main() {
  int n, m, a, r;
  scanf("%d %d %d %d", &n, &m, &a, &r);

  vector<int> f(n);
  for (int i = 0; i < n; ++i) scanf("%d", &f[i]);

  vector<int> ans(m);
  ll x = a;
  for (int j = 0; j < m; ++j) {
    ll pow_x = 1;
    ll fx = 0;
    for (int i = 0; i < n; ++i) {
      fx += f[i] * pow_x;
      fx %= mod;
      pow_x = pow_x * x % mod;
    }
    ans[j] = fx;
    x = x * r % mod;
  }

  for (int i = 0; i < m; i++) {
    printf("%d", ans[i]);
    if (i + 1 < m) printf(" ");
  }
  printf("\n");
  return 0;
}
