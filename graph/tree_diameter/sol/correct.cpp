#include <cstdio>
#include <vector>
#include <tuple>

using lint = long long int;
using Graph = std::vector<std::vector<std::pair<int, lint>>>;

template<typename T>
std::pair<T, int> dfs(const std::vector<std::vector<std::pair<int, T>>> &g, int cur, int par) {

  std::pair<T, int> ret(0, cur);
  for (auto e : g[cur]) {
    // auto [nxt, weight] = e;
    int nxt;
    lint weight;
    std::tie(nxt, weight) = e;
    if (nxt == par) continue;
    auto cost = dfs(g, nxt, cur);
    cost.first += weight;
    ret = max(ret, cost);
  }

  return ret;
}

template<typename T>
std::tuple<int, int, T> tree_diameter(const std::vector<std::vector<std::pair<int, T>>> &g) {

  // auto [_, u] = dfs(g, 0, -1); // c++ 17 は無理なのかな
  auto u = dfs(g, 0, -1).second;
  // auto [dist, v] = dfs(g, u, -1);
  T dist;
  int v;
  std::tie(dist, v) = dfs(g, u, -1);
  return std::make_tuple(u, v, dist);
}

template<typename T>
void path_restoration(const std::vector<std::vector<std::pair<int, T>>> &g, std::vector<int> &path, int cur, int par, int &goal) {
  path.push_back(cur);
  if (cur == goal) {
    goal = -1;
    return;
  }

  for (auto e : g[cur]) {
    // auto [nxt, _] = e;
    int nxt = e.first;
    if (nxt == par) continue;
    path_restoration(g, path, nxt, cur, goal);
    if (goal == -1) return;
  }

  if (goal == -1) {
    return;
  }
  path.pop_back();
}

int main() {

  int n;
  scanf("%d", &n);
  Graph g(n);
  for (int i = 0; i < n - 1; i++) {
    int a, b;
    lint c;
    scanf("%d %d %lld", &a, &b, &c);
    g[a].push_back({b, c});
    g[b].push_back({a, c});
  }

  // auto [u, v, dist] = tree_diameter<lint>(g);
  int u, v;
  lint dist;
  std::tie(u, v, dist) = tree_diameter<lint>(g);
  std::vector<int> path;
  path_restoration(g, path, u, -1, v);
  printf("%lld %zu\n", dist, path.size());
  for (size_t i = 0; i < path.size(); i++) {
    if (i + 1 == path.size()) {
      printf("%d\n", path[i]);
    } else {
      printf("%d ", path[i]);
    }
  }
  return 0;
}
