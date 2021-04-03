#include <algorithm>
#include <cstdio>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

int main() {
  using i64 = long long;
  static constexpr i64 mod = 998244353;

  int n, m;
  std::scanf("%d %d", &n, &m);
  std::vector<i64> xs(n);
  for (auto &x : xs) {
    scanf("%lld", &x);
  }
  std::vector<std::vector<int>> g(n);
  std::set<std::pair<int, int>> eset;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::scanf("%d %d", &u, &v);
    eset.insert(std::minmax(u, v));
    g[u].push_back(v);
    g[v].push_back(u);
  }

  i64 ans = 0;
  for (int a = 0; a < n; ++a) {
    for (int b : g[a]) {
      for (int c : g[a]) {
        if (eset.count({b, c})) {
          ans += xs[a] * xs[b] % mod * xs[c];
          ans %= mod;
        }
      }
    }
  }

  while (ans % 3 != 0) {
    ans += mod;
  }
  ans /= 3;

  std::printf("%lld\n", ans);
}
