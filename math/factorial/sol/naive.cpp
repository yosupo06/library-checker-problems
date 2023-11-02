#include <cstdio>

using namespace std;

constexpr int mod = 998244353;

void solve() {
  int N;
  scanf("%d", &N);

  long long ans = 1;
  for (int n = 1; n <= N; ++n) ans = ans * n % mod;
  printf("%lld", ans);
}

signed main() {
  solve();
  return 0;
}
