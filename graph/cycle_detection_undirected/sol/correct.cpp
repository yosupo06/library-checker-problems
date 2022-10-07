#include <cstdio>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

template <typename T>
using vc = vector<T>;
#define eb emplace_back

void solve() {
  int N, M;
  scanf("%d%d", &N, &M);

  // (to, eid)
  using P = pair<int, int>;
  vc<P> edges;
  vc<vc<P>> G(N);
  for (int m = 0; m < M; ++m) {
    int a, b;
    scanf("%d%d", &a, &b);
    edges.eb(a, b);
    G[a].eb(m, b);
    G[b].eb(m, a);
  }

  auto out_vec = [&](vc<int>& A) -> void {
    for (int i = 0; i < int(A.size()); ++i) {
      if (i) printf(" ");
      printf("%d", A[i]);
    }
    printf("\n");
  };

  // dfs tree
  vc<bool> used_e(M);
  vc<P> par(N, {-1, -1}); // (vid, eid)
  vc<int> dep(N, -1);
  auto dfs = [&](auto& dfs, int v, int d) -> void {
    assert(dep[v] == -1);
    dep[v] = d;
    for (auto&& [eid, to]: G[v]) {
      if (dep[to] != -1) continue;
      used_e[eid] = 1;
      par[to] = {v, eid};
      dfs(dfs, to, d + 1);
    }
  };

  for (int v = 0; v < N; ++v) {
    if (dep[v] == -1) dfs(dfs, v, 0);
  }

  auto check = [&](vc<int> V, vc<int> E) -> bool {
    int L = V.size();
    assert(L >= 1);
    vc<int> used_v(N), used_e(M);
    for (auto&& v: V) {
      if (used_v[v]) return false;
      used_v[v] = 1;
    }
    for (auto&& e: E) {
      if (used_e[e]) return false;
      used_e[e] = 1;
    }
    for (int i = 0; i < L; ++i) {
      auto [a, b] = edges[E[i]];
      int j = (i + 1 == L ? 0 : i + 1);
      bool ok = 0;
      if (V[i] == a && V[j] == b) ok = 1;
      if (V[i] == b && V[j] == a) ok = 1;
      if (!ok) return false;
    }
    return true;
  };

  for (int eid = 0; eid < M; ++eid) {
    if (used_e[eid]) continue;
    auto [a, b] = edges[eid];
    if (dep[a] > dep[b]) swap(a, b);
    assert(dep[a] <= dep[b]);

    // 後退辺 e から、サイクルが出来る
    vc<int> E, V = {b};
    while (V.back() != a) {
      auto [v, e] = par[V.back()];
      V.eb(v);
      E.eb(e);
    }
    E.eb(eid);
    assert(check(V, E));

    // 出力
    int L = V.size();
    printf("%d\n", L);
    out_vec(V);
    out_vec(E);
    return;
  }

  printf("%d\n", -1);
  return;
}

int main() {
  solve();
  return 0;
}