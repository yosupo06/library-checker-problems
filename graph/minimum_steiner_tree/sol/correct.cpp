#include <algorithm>
#include <array>
#include <cstdio>
#include <limits>
#include <numeric>
#include <queue>
#include <tuple>
#include <vector>

using namespace std;

template<class T>
pair<T, vector<int>> steiner_tree(int n, vector<int> s, vector<tuple<int, int, T>> e) {
  int k = 0;
  {
    vector<bool> in_s(n, false);
    for(int x : s) in_s[x] = true;
    for(int v = 0; v < n; v++) k += in_s[v];
    vector<int> f(n);
    int nxt = 0;
    for(bool x : {true, false})
      for(int v = 0; v < n; v++)
        if (in_s[v] == x)
          f[v] = nxt++;
    for(auto &[u, v, _] : e)
      u = f[u], v = f[v];
  }

  vector<vector<tuple<int, int, T>>> g(n);
  for(int i = 0; i < (int)size(e); i++) {
    auto [u, v, w] = e[i];
    g[u].emplace_back(v, i, w);
    g[v].emplace_back(u, i, w);
  }

  vector dp(1 << k, vector<T>(n, numeric_limits<T>::max()));
  vector pre(1 << k, vector<array<int, 2>>(n, {-1, -1}));

  for(int x = 1; x < (1 << k); x++) {
    if ((x & (-x)) == x) {
      int i = 0;
      while((1 << i) < x) i++;
      dp[x][i] = 0;
    } else {
      for(int r = 0; r < n; r++)
        for(int y = (x - 1) & x; y > 0; y = (y - 1) & x)
          if (T tmp = dp[y][r] + dp[x^y][r]; tmp < dp[x][r])
            dp[x][r] = tmp, pre[x][r] = {y, -1};
    }
    priority_queue<pair<T, int>, vector<pair<T, int>>, greater<pair<T, int>>> pq;
    for(int r = 0; r < n; r++)
      pq.push(make_pair(dp[x][r], r));
    while(!pq.empty()) {
      auto [d, v] = pq.top(); pq.pop();
      if (d != dp[x][v]) continue;
      for(auto [to, i, w] : g[v]) {
        if (d + w < dp[x][to]) {
          dp[x][to] = d + w, pre[x][to] = {v, i};
          pq.push(make_pair(d + w, to));
        }
      }
    }
  }

  vector<bool> in_t(size(e));
  auto dfs = [&](int x, int r, auto &&self) -> void {
    auto [a, b] = pre[x][r];
    if (a == -1) return;
    if (b == -1) {
      self(a, r, self);
      self(x ^ a, r, self);
    } else {
      in_t[b] = true;
      self(x, a, self);
    }
  };

  int best_r = min_element(dp.back().begin(), dp.back().end()) - dp.back().begin();
  dfs((1 << k) - 1, best_r, dfs);

  vector<int> t;
  for(int i = 0; i < (int)size(e); i++)
    if (in_t[i])
      t.emplace_back(i);

  return make_pair(dp.back()[best_r], t);
}

int main() {
  int N, M;
  scanf("%d %d", &N, &M);

  vector<tuple<int, int, long long>> E(M);
  for(auto &[u, v, w] : E)
    scanf("%d %d %lld", &u, &v, &w);

  int K;
  scanf("%d", &K);
  vector<int> X(K);
  for(int &x : X)
    scanf("%d", &x);

  auto [Y, T] = steiner_tree(N, X, E);
  printf("%lld %zu\n", Y, size(T));
  for(int i = 0; i < (int)size(T); i++) {
    printf("%d", T[i]);
    if (i + 1 != (int)size(T)) printf(" ");
  }
  printf("\n");

  return 0;
}
