// https://judge.yosupo.jp/submission/30757

#include <iostream>
#include <vector>
using namespace std;

template <typename G>
struct Tree {
 private:
  G& g;
  int root;
  vector<vector<int>> bl;
  vector<int> dp;
  void build() {
    bl.resize(g.size());
    dp.resize(g.size());
    dfs(root, -1, 0);
  }

  void dfs(int c, int p, int _dp) {
    dp[c] = _dp;
    for (int i = p, x = -1; i != -1;) {
      bl[c].push_back(i);
      i = ++x < (int)bl[i].size() ? bl[i][x] : -1;
    }
    for (auto& d : g[c]) {
      if (d == p) continue;
      dfs(d, c, _dp + 1);
    }
  }

 public:
  Tree(G& _g, int _r = 0) : g(_g), root(_r) { build(); }

  int kth_ancestor(int u, int k) const {
    for (int i = 30; i >= 0; --i) {
      if ((k >> i) & 1) {
        if (i >= (int)bl[u].size()) return -1;
        u = bl[u][i];
      }
    }
    return u;
  }

  int lca(int u, int v) {
    while (u != v) {
      if (dp[u] > dp[v]) swap(u, v);
      v = kth_ancestor(v, max(1, dp[v] - dp[u]));
    }
    return v;
  }
};

int main() {
  ios::sync_with_stdio(false);
  cin.tie(nullptr);
  int N, Q;
  cin >> N >> Q;
  using vvi = vector<vector<int>>;
  vvi g(N);
  for (int i = 1; i <= N - 1; i++) {
    int p;
    cin >> p;
    g[p].push_back(i);
  }
  Tree<vvi> tree(g);
  while (Q--) {
    int u, v;
    cin >> u >> v;
    cout << tree.lca(u, v) << '\n';
  }
}
