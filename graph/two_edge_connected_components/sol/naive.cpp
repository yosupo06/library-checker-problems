#include <cstddef>
#include <functional>
#include <vector>

using usize = std::size_t;

std::vector<std::vector<usize>>
teccd_naive(const std::vector<std::vector<usize>> g) {
  const usize n = g.size();
  std::vector<std::vector<usize>> cap_(n, std::vector<usize>(n, 0));
  for (usize i = 0; i != n; i += 1) {
    for (const usize j : g[i])
      cap_[i][j] += 1;
  }
  const auto is_2_con = [&](const usize s, const usize t) -> bool {
    auto cap = cap_;
    std::vector<bool> visited(n, false);
    const std::function<bool(usize)> dfs = [&](const usize v) -> bool {
      visited[v] = true;
      if (v == t)
        return true;
      for (usize w = 0; w != n; w += 1) {
        if (cap[v][w] > 0 && !visited[w]) {
          if (dfs(w)) {
            cap[v][w] -= 1;
            cap[w][v] += 1;
            return true;
          }
        }
      }
      return false;
    };
    for (usize i = 0; i != 2; i += 1) {
      if (!dfs(s))
        return false;
      std::fill(visited.begin(), visited.end(), false);
    }
    return true;
  };
  std::vector<std::vector<usize>> res;
  std::vector<bool> visited(n, false);
  for (usize s = 0; s != n; s += 1) {
    if (visited[s])
      continue;
    visited[s] = true;
    res.push_back({s});
    for (usize t = 0; t != n; t += 1) {
      if (visited[t])
        continue;
      if (is_2_con(s, t)) {
        res.back().push_back(t);
        visited[t] = true;
      }
    }
  }
  return res;
}

#include <cstdio>
#include <cstdlib>

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n > 100)
    std::abort();
  std::vector<std::vector<usize>> g(n);
  for (int i = 0; i != m; i += 1) {
    int a, b;
    scanf("%d%d", &a, &b);
    g[a].push_back(b);
    g[b].push_back(a);
  }
  const auto ans = teccd_naive(g);
  printf("%d\n", static_cast<int>(ans.size()));
  for (const auto &l : ans) {
    printf("%d", static_cast<int>(l.size()));
    for (const auto v : l)
      printf(" %d", static_cast<int>(v));
    printf("\n");
  }
}
