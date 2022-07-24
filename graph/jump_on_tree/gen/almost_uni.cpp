#include <iostream>
#include <tuple>
#include <vector>

#include "../params.h"
#include "random.h"

using namespace std;

template <class T, class S>
inline bool chmax(T& a, const S& b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T& a, const S& b) {
  return (a > b ? a = b, 1 : 0);
}

template <class T>
using vc = vector<T>;

template <typename T>
struct Edge {
  int frm, to;
  T cost;
  int id;
};

template <typename T = int, bool directed = false>
struct Graph {
  int N, M;
  using cost_type = T;
  using edge_type = Edge<T>;
  vector<edge_type> edges;
  vector<int> indptr;
  vector<edge_type> csr_edges;
  bool prepared;

  class OutgoingEdges {
  public:
    OutgoingEdges(const Graph* G, int l, int r) : G(G), l(l), r(r) {}

    const edge_type* begin() const {
      if (l == r) { return 0; }
      return &G->csr_edges[l];
    }

    const edge_type* end() const {
      if (l == r) { return 0; }
      return &G->csr_edges[r];
    }

  private:
    const Graph* G;
    int l, r;
  };

  bool is_prepared() { return prepared; }
  constexpr bool is_directed() { return directed; }

  Graph() : N(0), M(0), prepared(0) {}
  Graph(int N) : N(N), M(0), prepared(0) {}

  void build() {
    assert(!prepared);
    prepared = true;
    indptr.assign(N + 1, 0);
    for (auto&& e: edges) {
      indptr[e.frm + 1]++;
      if (!directed) indptr[e.to + 1]++;
    }
    for (int v = 0; v < N; ++v) { indptr[v + 1] += indptr[v]; }
    auto counter = indptr;
    csr_edges.resize(indptr.back() + 1);
    for (auto&& e: edges) {
      csr_edges[counter[e.frm]++] = e;
      if (!directed)
        csr_edges[counter[e.to]++] = edge_type({e.to, e.frm, e.cost, e.id});
    }
  }

  void add(int frm, int to, T cost = 1, int i = -1) {
    assert(!prepared);
    assert(0 <= frm && 0 <= to && to < N);
    if (i == -1) i = M;
    auto e = edge_type({frm, to, cost, i});
    edges.emplace_back(e);
    ++M;
  }
  OutgoingEdges operator[](int v) const {
    assert(prepared);
    return {this, indptr[v], indptr[v + 1]};
  }
};

template <typename Graph>
struct HLD {
  Graph& G;
  using Graph_type = Graph;
  using WT = typename Graph::cost_type;
  int N;
  vector<int> LID, RID, head, V, parent, root;
  vc<int> depth;
  vc<WT> depth_weighted;
  vector<bool> in_tree;

  HLD(Graph& G, int r = -1)
      : G(G),
        N(G.N),
        LID(G.N),
        RID(G.N),
        head(G.N, r),
        V(G.N),
        parent(G.N, -1),
        root(G.N, -1),
        depth(G.N, -1),
        depth_weighted(G.N, 0),
        in_tree(G.M, 0) {
    assert(G.is_prepared());
    int t1 = 0;
    if (r != -1) {
      dfs_sz(r, -1);
      dfs_hld(r, t1);
    } else {
      for (int r = 0; r < N; ++r) {
        if (parent[r] == -1) {
          head[r] = r;
          dfs_sz(r, -1);
          dfs_hld(r, t1);
        }
      }
    }
    for (auto&& v: V) root[v] = (parent[v] == -1 ? v : root[parent[v]]);
  }

  void dfs_sz(int v, int p) {
    auto& sz = RID;
    parent[v] = p;
    depth[v] = (p == -1 ? 0 : depth[p] + 1);
    sz[v] = 1;
    int l = G.indptr[v], r = G.indptr[v + 1];
    auto& csr = G.csr_edges;
    // 使う辺があれば先頭にする
    for (int i = r - 2; i >= l; --i) {
      if (depth[csr[i + 1].to] == -1) swap(csr[i], csr[i + 1]);
    }
    int hld_sz = 0;
    for (int i = l; i < r; ++i) {
      auto e = csr[i];
      if (depth[e.to] != -1) continue;
      in_tree[e.id] = 1;
      depth_weighted[e.to] = depth_weighted[v] + e.cost;
      dfs_sz(e.to, v);
      sz[v] += sz[e.to];
      if (chmax(hld_sz, sz[e.to]) && l < i) { swap(csr[l], csr[i]); }
    }
  }

  void dfs_hld(int v, int& times) {
    LID[v] = times++;
    RID[v] += LID[v];
    V[LID[v]] = v;
    bool heavy = true;
    for (auto&& e: G[v]) {
      if (!in_tree[e.id] || depth[e.to] <= depth[v]) continue;
      head[e.to] = (heavy ? head[v] : e.to);
      heavy = false;
      dfs_hld(e.to, times);
    }
  }

  /* k: 0-indexed */
  int LA(int v, int k) {
    assert(k <= depth[v]);
    while (1) {
      int u = head[v];
      if (LID[v] - k >= LID[u]) return V[LID[v] - k];
      k -= LID[v] - LID[u] + 1;
      v = parent[u];
    }
  }

  int LCA(int u, int v) {
    for (;; v = parent[head[v]]) {
      if (LID[u] > LID[v]) swap(u, v);
      if (head[u] == head[v]) return u;
    }
  }

  int lca(int u, int v) { return LCA(u, v); }
  int la(int u, int v) { return LA(u, v); }

  int subtree_size(int v) { return RID[v] - LID[v]; }

  int dist(int a, int b) {
    int c = LCA(a, b);
    return depth[a] + depth[b] - 2 * depth[c];
  }
};

int main(int, char* argv[]) {
  long long seed = atoll(argv[1]);
  auto gen = Random(seed);

  int N = N_MAX;
  int Q = Q_MAX;

  using edge = std::pair<int, int>;
  std::vector<edge> edges;
  for (int i = 1; i < N * 9 / 10; i++) { edges.emplace_back(0, i); }
  for (int i = N * 9 / 10; i < N; i++) {
    edges.emplace_back(gen.uniform(0, i - 1), i);
  }

  gen.shuffle(edges.begin(), edges.end());
  printf("%d %d\n", N, Q);
  Graph<int, 0> G(N);
  for (auto e: edges) {
    int u, v;
    std::tie(u, v) = e;
    printf("%d %d\n", u, v);
    G.add(u, v);
  }
  G.build();
  HLD<decltype(G)> hld(G);

  for (int q = 0; q < Q; ++q) {
    int s = gen.uniform<int>(0, N - 1);
    int t = gen.uniform<int>(0, N - 1);
    int dst = hld.dist(s, t);
    int i;
    if (gen.uniform<int>(0, 9) == 0) {
      i = gen.uniform<int>(0, N - 1);
    } else {
      i = gen.uniform<int>(0, dst);
    }
    printf("%d %d %d\n", s, t, i);
  }
  return 0;
}
