#include <bits/stdc++.h>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'000'000'000;

using pi = pair<ll, ll>;
using vi = vector<ll>;
template <class T>
using vc = vector<T>;

#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define overload4(a, b, c, d, e, ...) e
#define overload3(a, b, c, d, ...) d
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) overload3(__VA_ARGS__, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))

template <class T, class S>
inline bool chmax(T& a, const S& b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T& a, const S& b) {
  return (a > b ? a = b, 1 : 0);
}

struct UnionFind {
  int n, n_comp;
  vc<int> dat; // par or (-size)
  UnionFind(int n = 0) { build(n); }

  void build(int m) {
    n = m, n_comp = m;
    dat.assign(n, -1);
  }

  void reset() { build(n); }

  int operator[](int x) {
    while (dat[x] >= 0) {
      int pp = dat[dat[x]];
      if (pp < 0) { return dat[x]; }
      x = dat[x] = pp;
    }
    return x;
  }

  bool merge(int x, int y) {
    x = (*this)[x], y = (*this)[y];
    if (x == y) return false;
    if (-dat[x] < -dat[y]) swap(x, y);
    dat[x] += dat[y], dat[y] = x, n_comp--;
    return true;
  }
};

template <typename T>
struct Edge {
  int frm, to;
  T cost;
  int id;
};

template <typename T = int, bool directed = false>
struct Graph {
  static constexpr bool is_directed = directed;
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

  Graph() : N(0), M(0), prepared(0) {}
  Graph(int N) : N(N), M(0), prepared(0) {}

  void build(int n) {
    N = n, M = 0;
    prepared = 0;
    edges.clear();
    indptr.clear();
    csr_edges.clear();
  }

  void add(int frm, int to, T cost = 1, int i = -1) {
    assert(!prepared);
    assert(0 <= frm && 0 <= to && to < N);
    if (i == -1) i = M;
    auto e = edge_type({frm, to, cost, i});
    edges.eb(e);
    ++M;
  }

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

  OutgoingEdges operator[](int v) const {
    assert(prepared);
    return {this, indptr[v], indptr[v + 1]};
  }
};

/*
block-cut tree を、block に通常の頂点を隣接させて拡張しておく
https://twitter.com/noshi91/status/1529858538650374144?s=20&t=eznpFbuD9BDhfTb4PplFUg
[0, n)：もとの頂点 [n, n + n_block)：block
関節点：[0, n) のうちで、degree >= 2 を満たすもの
孤立点は、1 点だけからなる block
成分が欲しい場合：近傍を見ると点集合. 辺から成分を得るには tree.jump
と思ったが非連結なときに注意がいるな…
*/
template <typename GT>
Graph<int, 0> block_cut(GT& G) {
  int n = G.N;
  vc<int> low(n), ord(n), st;
  vc<bool> used(n);
  st.reserve(n);
  int nxt = n;
  int k = 0;
  vc<pair<int, int>> edges;

  auto dfs = [&](auto& dfs, int v, int p) -> void {
    st.eb(v);
    used[v] = 1;
    low[v] = ord[v] = k++;
    int child = 0;
    for (auto&& e: G[v]) {
      if (e.to == p) continue;
      if (!used[e.to]) {
        ++child;
        int s = len(st);
        dfs(dfs, e.to, v);
        chmin(low[v], low[e.to]);
        if ((p == -1 && child > 1) || (p != -1 && low[e.to] >= ord[v])) {
          edges.eb(nxt, v);
          while (len(st) > s) {
            edges.eb(nxt, st.back());
            st.pop_back();
          }
          ++nxt;
        }
      } else {
        chmin(low[v], ord[e.to]);
      }
    }
  };
  FOR(v, n) if (!used[v]) {
    dfs(dfs, v, -1);
    for (auto&& x: st) { edges.eb(nxt, x); }
    ++nxt;
    st.clear();
  }
  Graph<int, 0> BCT(nxt);
  for (auto&& [a, b]: edges) BCT.add(a, b);
  BCT.build();
  return BCT;
}

template <typename T, typename GT>
pair<vc<T>, vc<int>> bfs01(GT& G, int v) {
  assert(G.is_prepared());
  int N = G.N;
  vc<T> dist(N, infty<T>);
  vc<int> par(N, -1);
  deque<int> que;

  dist[v] = 0;
  que.push_front(v);
  while (!que.empty()) {
    auto v = que.front();
    que.pop_front();
    for (auto&& e: G[v]) {
      if (dist[e.to] == infty<T> || dist[e.to] > dist[e.frm] + e.cost) {
        dist[e.to] = dist[e.frm] + e.cost;
        par[e.to] = e.frm;
        if (e.cost == 0)
          que.push_front(e.to);
        else
          que.push_back(e.to);
      }
    }
  }
  return {dist, par};
}

vector<int> restore_path(vector<int> par, int t) {
  vector<int> pth = {t};
  while (par[pth.back()] != -1) pth.eb(par[pth.back()]);
  reverse(all(pth));
  return pth;
}

// https://en.wikipedia.org/wiki/Bipolar_orientation
// 順列 p を求める. p[s]=0,p[t]=n-1.
// p[u]<p[v] となる向きに辺を向き付けると任意の v に対して svt パスが存在.
// 存在条件：BCT で全部の成分を通る st パスがある 不可能ならば empty をかえす.
template <typename GT>
vc<int> st_numbering(GT& G, int s, int t) {
  static_assert(!GT::is_directed);
  assert(G.is_prepared());
  int N = G.N;
  if (N == 1) return {0};
  if (s == t) return {};
  vc<int> par(N, -1), pre(N, -1), low(N, -1);
  vc<int> V;

  auto dfs = [&](auto& dfs, int v) -> void {
    pre[v] = len(V), V.eb(v);
    low[v] = v;
    for (auto& e: G[v]) {
      int w = e.to;
      if (v == w) continue;
      if (pre[w] == -1) {
        dfs(dfs, w);
        par[w] = v;
        if (pre[low[w]] < pre[low[v]]) { low[v] = low[w]; }
      }
      elif (pre[w] < pre[low[v]]) { low[v] = w; }
    }
  };

  pre[s] = 0, V.eb(s);
  dfs(dfs, t);
  if (len(V) != N) return {};
  vc<int> nxt(N, -1), prev(N);
  nxt[s] = t, prev[t] = s;

  vc<int> sgn(N);
  sgn[s] = -1;
  FOR(i, 2, len(V)) {
    int v = V[i];
    int p = par[v];
    if (sgn[low[v]] == -1) {
      int q = prev[p];
      if (q == -1) return {};
      nxt[q] = v, nxt[v] = p;
      prev[v] = q, prev[p] = v;
      sgn[p] = 1;
    } else {
      int q = nxt[p];
      if (q == -1) return {};
      nxt[p] = v, nxt[v] = q;
      prev[v] = p, prev[q] = v;
      sgn[p] = -1;
    }
  }
  vc<int> A = {s};
  while (A.back() != t) { A.eb(nxt[A.back()]); }
  // 作れているか判定
  if (len(A) < N) return {};
  assert(A[0] == s && A.back() == t);
  vc<int> rk(N, -1);
  FOR(i, N) rk[A[i]] = i;
  assert(MIN(rk) != -1);
  FOR(i, N) {
    bool l = 0, r = 0;
    int v = A[i];
    for (auto& e: G[v]) {
      if (rk[e.to] < rk[v]) l = 1;
      if (rk[v] < rk[e.to]) r = 1;
    }
    if (i > 0 && !l) return {};
    if (i < N - 1 && !r) return {};
  }
  vc<int> res(N);
  FOR(i, N) res[A[i]] = i;
  return res;
}

bool check_st_numbering(Graph<int, 0> G, int s, int t) {
  int N = G.N;
  assert(N >= 2);

  UnionFind uf(N);
  for (auto& e: G.edges) uf.merge(e.frm, e.to);
  if (uf.n_comp >= 2) return 0; // disconnected

  // BCT において st パスがすべての block を通ることが必要
  auto BCT = block_cut(G);
  auto [dist, par] = bfs01<int>(BCT, s);
  vc<int> path = restore_path(par, t);

  vc<int> vis(BCT.N);
  for (auto& x: path) vis[x] = 1;

  FOR(i, N, BCT.N) {
    if (!vis[i]) return 0;
  }
  return 1;
}

void solve() {
  int N, M, s, t;
  scanf("%d %d %d %d", &N, &M, &s, &t);
  Graph<int, 0> G(N);
  for (int m = 0; m < M; ++m) {
    int a, b;
    scanf("%d %d", &a, &b);
    G.add(a, b);
  }
  G.build();

  bool ch = check_st_numbering(G, s, t);
  vc<int> p = st_numbering(G, s, t);
  assert(ch == (!p.empty()));

  if (p.empty()) {
    printf("No\n");
    return;
  }
  printf("Yes\n");
  for (int i = 0; i < N; ++i) {
    if (i) printf(" ");
    printf("%d", p[i]);
  }
  printf("\n");
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
  return 0;
}
