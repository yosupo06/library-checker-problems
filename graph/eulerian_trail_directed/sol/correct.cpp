#include <vector>
#include <map>
#include <algorithm>
#include <cassert>
#include <cstdio>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

using pi = pair<ll, ll>;
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

#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename T>
T POP(vc<T>& que) {
  T a = que.back();
  que.pop_back();
  return a;
}

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

template <typename GT>
vc<int> vs_to_es(GT& G, vc<int>& vs) {
  assert(!vs.empty());
  map<pair<int, int>, vc<int>> MP;

  auto to_pair = [&](int a, int b) -> pair<int, int> {
    if (GT::is_directed) return {a, b};
    if (a > b) swap(a, b);
    return {a, b};
  };

  FOR(eid, G.M) {
    pair<int, int> p = to_pair(G.edges[eid].frm, G.edges[eid].to);
    MP[p].eb(eid);
  }
  int n = len(vs);
  vc<int> es(n - 1);
  FOR(i, n - 1) {
    pair<int, int> p = to_pair(vs[i], vs[i + 1]);
    assert(!MP[p].empty());
    es[i] = POP(MP[p]);
  }
  return es;
}

// (vs, es) or empty
template <typename GT>
pair<vc<int>, vc<int>> euler_walk(GT& G, int s = -1) {
  const int N = G.N, M = G.M;
  assert(G.is_prepared());
  assert(N > 0);

  if (s == -1) {
    vc<int> deg(N);
    for (auto&& e: G.edges) {
      if constexpr (GT::is_directed) {
        deg[e.frm]++, deg[e.to]--;
      } else {
        deg[e.frm]++, deg[e.to]++;
      }
    }
    if constexpr (GT::is_directed) {
      s = max_element(all(deg)) - deg.begin();
      if (deg[s] == 0) s = (M == 0 ? 0 : G.edges[0].frm);
    } else {
      s = [&]() -> int {
        FOR(v, N) if (deg[v] & 1) return v;
        return (M == 0 ? 0 : G.edges[0].frm);
      }();
    }
  }

  if (M == 0) return {{s}, {}};
  vc<int> D(N), its(N), eu(M), vs, st = {s};
  FOR(v, N) its[v] = G.indptr[v];
  ++D[s];
  while (!st.empty()) {
    int x = st.back(), y, e, &it = its[x], end = G.indptr[x + 1];
    if (it == end) {
      vs.eb(x);
      st.pop_back();
      continue;
    }
    auto& ee = G.csr_edges[it++];
    y = ee.to, e = ee.id;
    if (!eu[e]) {
      D[x]--, D[y]++;
      eu[e] = 1;
      st.eb(y);
    }
  }
  for (auto&& x: D)
    if (x < 0) return {{}, {}};
  if (len(vs) != M + 1) return {{}, {}};
  reverse(all(vs));
  auto es = vs_to_es(G, vs);
  return {vs, es};
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

  ll size(int x) {
    x = (*this)[x];
    return -dat[x];
  }

  bool merge(int x, int y) {
    x = (*this)[x], y = (*this)[y];
    if (x == y) return false;
    if (-dat[x] < -dat[y]) swap(x, y);
    dat[x] += dat[y], dat[y] = x, n_comp--;
    return true;
  }
};

// LC 用新規実装
bool has_eulerian_trail(Graph<int, 1> G) {
  int N = G.N;
  vc<int> in(N), out(N);
  for (auto& e: G.edges) out[e.frm]++, in[e.to]++;

  int ng = 0;
  FOR(v, N) ng += abs(out[v] - in[v]);
  if (ng >= 4) return false;

  UnionFind uf(N);
  for (auto& e: G.edges) uf.merge(e.frm, e.to);
  vector<int> cnt_edge(N);
  for (auto& e: G.edges) cnt_edge[uf[e.frm]]++;

  // 辺がある成分を数える
  int nc = 0;
  for (int v = 0; v < N; ++v) {
    if (uf[v] == v && cnt_edge[v] >= 1) ++nc;
  }
  return nc <= 1;
}

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);
  Graph<int, 1> G(N);
  FOR(M) {
    int a, b;
    scanf("%d %d", &a, &b);
    G.add(a, b);
  }
  G.build();
  auto [vs, es] = euler_walk(G);
  if (vs.empty()) {
    assert(!has_eulerian_trail(G));
    printf("No\n");
  } else {
    printf("Yes\n");
    for (int i = 0; i < len(vs); ++i) {
      if (i) printf(" ");
      printf("%d", vs[i]);
    }
    printf("\n");
    for (int i = 0; i < len(es); ++i) {
      if (i) printf(" ");
      printf("%d", es[i]);
    }
    printf("\n");
  }
}

int main() {
  int T;
  scanf("%d", &T);
  for (int t = 0; t < T; ++t) solve();
  return 0;
}
