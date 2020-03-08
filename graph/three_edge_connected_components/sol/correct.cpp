#include <algorithm>
#include <cassert>
#include <cstddef>
#include <cstdio>
#include <functional>
#include <numeric>
#include <utility>
#include <vector>

using usize = std::size_t;

class union_enumerate {
  std::vector<usize> next;

public:
  union_enumerate() = default;
  union_enumerate(const usize size) : next(size) {
    std::iota(next.begin(), next.end(), static_cast<usize>(0));
  }

  usize size() const { return next.size(); }

  std::vector<usize> enumerate(const usize x) const {
    assert(x < size());

    std::vector<usize> ret;
    usize y = x;
    do {
      ret.push_back(y);
      y = next[y];
    } while (y != x);
    return ret;
  }

  std::vector<std::vector<usize>> get_all() const {
    const usize n = size();
    std::vector<std::vector<usize>> res;
    std::vector<bool> visited(n, false);
    for (usize i = 0; i != n; i += 1) {
      if (!visited[i]) {
        const std::vector<usize> list = enumerate(i);
        for (const usize j : list)
          visited[j] = true;
        res.push_back(list);
      }
    }
    return res;
  }

  void unite(const usize x, const usize y) {
    assert(x < size());
    assert(y < size());

    std::swap(next[x], next[y]);
  }
};

std::vector<std::vector<usize>> three_edge_connected_component_decomposition(
    const std::vector<std::vector<usize>> g) {
  const usize n = g.size();
  std::vector<usize> in(n);
  std::vector<usize> out(n);
  std::vector<usize> low(n, n);
  std::vector<usize> deg(n, 0);
  std::vector<usize> path(n, n);
  std::vector<bool> visited(n, false);
  union_enumerate tcc(n);

  const auto absorb = [&](const usize v, const usize w) -> void {
    tcc.unite(v, w);
    deg[v] += deg[w];
  };

  usize count = 0;

  const std::function<void(usize, usize)> dfs = [&](const usize v,
                                                    usize p) -> void {
    visited[v] = true;
    in[v] = count;
    count += 1;

    for (usize w : g[v]) {
      if (w == v)
        continue;
      if (w == p) {
        p = n;
        continue;
      }
      if (visited[w]) {
        if (in[w] < in[v]) {
          deg[v] += 1;
          low[v] = std::min(low[v], in[w]);
        } else {
          deg[v] -= 1;
          usize u = path[v];
          while (u != n && in[u] <= in[w] && in[w] < out[u]) {
            absorb(v, u);
            u = path[u];
          }
          path[v] = u;
        }
        continue;
      }
      dfs(w, v);
      if (path[w] == n && deg[w] <= 1) {
        deg[v] += deg[w];
        low[v] = std::min(low[v], low[w]);
        continue;
      } else if (deg[w] == 0) {
        w = path[w];
      }
      if (low[w] < low[v]) {
        low[v] = low[w];
        std::swap(w, path[v]);
      }
      while (w != n) {
        absorb(v, w);
        w = path[w];
      }
    }

    out[v] = count;
  };

  for (usize i = 0; i != n; i += 1) {
    if (!visited[i])
      dfs(i, n);
  }

  return tcc.get_all();
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<std::vector<usize>> g(n);
  for (int i = 0; i != m; i += 1) {
    int a, b;
    scanf("%d%d", &a, &b);
    g[a].push_back(b);
    g[b].push_back(a);
  }
  const auto ans = three_edge_connected_component_decomposition(g);
  printf("%d\n", static_cast<int>(ans.size()));
  for (const auto &l : ans) {
    printf("%d", static_cast<int>(l.size()));
    for (const auto e : l)
      printf(" %d", static_cast<int>(e));
    printf("\n");
  }
}
