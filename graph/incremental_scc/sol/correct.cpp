#include <vector>
#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstdlib>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

template <class T>
using vc = vector<T>;

template <class T>
constexpr T infty = 0;
template <>
constexpr int infty<int> = 1'000'000'000;

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
#define fi first
#define se second

template <typename T>
T POP(vc<T> &que) {
  T a = que.back();
  que.pop_back();
  return a;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
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
    OutgoingEdges(const Graph *G, int l, int r) : G(G), l(l), r(r) {}

    const edge_type *begin() const {
      if (l == r) { return 0; }
      return &G->csr_edges[l];
    }

    const edge_type *end() const {
      if (l == r) { return 0; }
      return &G->csr_edges[r];
    }

  private:
    const Graph *G;
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
    for (auto &&e: edges) {
      indptr[e.frm + 1]++;
      if (!directed) indptr[e.to + 1]++;
    }
    for (int v = 0; v < N; ++v) { indptr[v + 1] += indptr[v]; }
    auto counter = indptr;
    csr_edges.resize(indptr.back() + 1);
    for (auto &&e: edges) {
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

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;

  constexpr modint() : val(0) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
};

using modint107 = modint<1000000007>;
using modint998 = modint<998244353>;

template <typename GT>
pair<int, vc<int>> strongly_connected_component(GT &G) {
  static_assert(GT::is_directed);
  assert(G.is_prepared());
  int N = G.N;
  int C = 0;
  vc<int> comp(N), low(N), ord(N, -1), path;
  int now = 0;

  auto dfs = [&](auto &dfs, int v) -> void {
    low[v] = ord[v] = now++;
    path.eb(v);
    for (auto &&[frm, to, cost, id]: G[v]) {
      if (ord[to] == -1) {
        dfs(dfs, to), chmin(low[v], low[to]);
      } else {
        chmin(low[v], ord[to]);
      }
    }
    if (low[v] == ord[v]) {
      while (1) {
        int u = POP(path);
        ord[u] = N, comp[u] = C;
        if (u == v) break;
      }
      ++C;
    }
  };
  FOR(v, N) {
    if (ord[v] == -1) dfs(dfs, v);
  }
  FOR(v, N) comp[v] = C - 1 - comp[v];
  return {C, comp};
}

template <typename GT>
vc<int> incremental_scc(GT &G) {
  static_assert(GT::is_directed);
  int N = G.N, M = G.M;
  vc<int> merge_time(M, infty<int>);
  vc<tuple<int, int, int>> dat;
  FOR(i, M) {
    auto &e = G.edges[i];
    dat.eb(i, e.frm, e.to);
  }

  vc<int> new_idx(N, -1);
  // L 時点ではサイクルには含まれず, R 時点では含まれる
  auto dfs
      = [&](auto &dfs, vc<tuple<int, int, int>> &dat, int L, int R) -> void {
    if (dat.empty() || R == L + 1) return;
    int M = (L + R) / 2;
    int n = 0;
    for (auto &[i, a, b]: dat) {
      if (new_idx[a] == -1) new_idx[a] = n++;
      if (new_idx[b] == -1) new_idx[b] = n++;
    }

    Graph<int, 1> G(n);
    for (auto &[i, a, b]: dat) {
      if (i < M) G.add(new_idx[a], new_idx[b]);
    }
    G.build();
    auto [nc, comp] = strongly_connected_component(G);
    vc<tuple<int, int, int>> dat1, dat2;
    for (auto [i, a, b]: dat) {
      a = new_idx[a], b = new_idx[b];
      if (i < M) {
        if (comp[a] == comp[b]) {
          chmin(merge_time[i], M), dat1.eb(i, a, b);
        } else {
          dat2.eb(i, comp[a], comp[b]);
        }
      } else {
        dat2.eb(i, comp[a], comp[b]);
      }
    }
    for (auto &[i, a, b]: dat) new_idx[a] = new_idx[b] = -1;
    dfs(dfs, dat1, L, M), dfs(dfs, dat2, M, R);
  };
  dfs(dfs, dat, 0, M + 1);
  return merge_time;
}

struct UnionFind {
  int n, n_comp;
  vc<int> dat; // par or (-size)
  UnionFind(int n = 0) { build(n); }

  void build(int m) {
    n = m, n_comp = m;
    dat.assign(n, -1);
  }
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

using mint = modint998;

void solve() {
  int N, M;
  scanf("%d %d", &N, &M);

  vc<mint> X(N);
  FOR(i, N) {
    int x;
    scanf("%d", &x);
    X[i] = x;
  }

  Graph<int, 1> G(N);
  FOR(M) {
    int a, b;
    scanf("%d %d", &a, &b);
    G.add(a, b);
  }

  auto time = incremental_scc(G);
  vc<vc<int>> IDS(M + 1);
  FOR(i, M) {
    if (time[i] != infty<int>) IDS[time[i]].eb(i);
  }

  UnionFind uf(N);
  mint ANS = 0;
  FOR(t, 1, M + 1) {
    for (auto &i: IDS[t]) {
      int a = G.edges[i].frm;
      int b = G.edges[i].to;
      a = uf[a], b = uf[b];
      if (a == b) continue;
      ANS += X[a] * X[b];
      uf.merge(a, b);
      X[uf[a]] = X[a] + X[b];
    }
    printf("%d\n", ANS.val);
  }
}

signed main() { solve(); }
