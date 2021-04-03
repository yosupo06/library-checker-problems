#include <cstdio>
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
  for (auto &e : edges) {
    int &u = e.first;
    int &v = e.second;
    std::scanf("%d %d", &u, &v);
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
  std::vector<bool> adj(n, false);
  for (const auto &e : edges) {
    int a = e.first;
    int b = e.second;
    for (auto c : g[a]) {
      adj[c] = true;
    }
    for (auto c : g[b]) {
      if (adj[c]) {
        ans += xs[a] * xs[b] % mod * xs[c];
        ans %= mod;
      }
    }
    for (auto c : g[a]) {
      adj[c] = false;
    }
  }

  std::printf("%lld\n", ans);
}
