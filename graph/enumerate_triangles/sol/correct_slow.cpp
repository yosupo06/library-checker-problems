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
  std::vector<std::pair<int, int>> edges(m);
  std::set<std::pair<int, int>> eset;
  for (auto &e : edges) {
    int &u = e.first;
    int &v = e.second;
    std::scanf("%d %d", &u, &v);
    eset.insert(std::minmax(u, v));
  }

  std::vector<int> deg(n, 0);
  for (const auto &e : edges) {
    int u = e.first;
    int v = e.second;
    deg[u] += 1;
    deg[v] += 1;
  }

  std::vector<std::vector<int>> g(n);
  for (const auto &e : edges) {
    int u = e.first;
    int v = e.second;
    if (std::tie(deg[u], u) > std::tie(deg[v], v)) {
      std::swap(u, v);
    }
    g[u].push_back(v);
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

  std::printf("%lld\n", ans);
}
