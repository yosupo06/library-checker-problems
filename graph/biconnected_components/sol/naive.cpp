#include <cstdio>
#include <cstdlib>
#include <functional>
#include <utility>
#include <vector>

using usize = std::size_t;

std::vector<std::vector<usize>>
bcd_naive(const usize n, const std::vector<std::pair<usize, usize>> es) {
  const usize m = es.size();
  const auto is_2_con = [&](const usize s, const usize t) -> bool {
    // remove vertex i
    for (usize i = 0; i != n; i += 1) {
      std::vector<bool> visited(n, false);
      visited[es[s].first] = true;
      visited[es[s].second] = true;
      visited[i] = false;
      for (usize j = 0; j != m; j += 1) {
        for (auto e : es) {
          if (visited[e.first] || visited[e.second])
            visited[e.first] = visited[e.second] = true;
          visited[i] = false;
        }
      }
      if (!visited[es[t].first] && !visited[es[t].second])
        return false;
    }
    return true;
  };
  std::vector<std::vector<usize>> res;
  std::vector<bool> visited(m, false);
  for (usize s = 0; s != m; s += 1) {
    if (visited[s])
      continue;
    visited[s] = true;
    res.push_back({s});
    for (usize t = 0; t != m; t += 1) {
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

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  if (n > 100 || m > 100)
    std::abort();

  std::vector<std::pair<usize, usize>> es;
  for (int i = 0; i != m; i += 1) {
    int a, b;
    scanf("%d%d", &a, &b);
    es.emplace_back(a, b);
  }

  const auto ans = bcd_naive(n, es);
  printf("%d\n", static_cast<int>(ans.size()));
  for (const auto &l : ans) {
    printf("%d", static_cast<int>(l.size()));
    for (const auto v : l)
      printf(" %d", static_cast<int>(v));
    printf("\n");
  }
}
