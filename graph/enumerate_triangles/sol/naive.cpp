#include <algorithm>
#include <cstdio>
#include <set>
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
  std::set<std::pair<int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int u, v;
    std::scanf("%d %d", &u, &v);
    edges.insert(std::minmax({u, v}));
  }

  i64 ans = 0;
  for (int a = 0; a < n; ++a) {
    for (int b = 0; b < a; ++b) {
      for (int c = 0; c < b; ++c) {
        if (edges.count({c, b}) && edges.count({c, a}) && edges.count({b, a})) {
          ans += xs[a] * xs[b] % mod * xs[c];
          ans %= mod;
        }
      }
    }
  }

  std::printf("%lld\n", ans);
}
