#include <cstdio>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

using vi = vector<ll>;
template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

#define vv(type, name, h, ...) \
  vector<vector<type>> name(h, vector<type>(__VA_ARGS__))

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
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

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

template <typename mint>
mint fact(int n) {
  static const int mod = mint::get_mod();
  assert(0 <= n && n < mod);
  static vector<mint> dat = {1, 1};
  while (len(dat) <= n) dat.eb(dat[len(dat) - 1] * mint::raw(len(dat)));
  return dat[n];
}

template <int mod>
struct modint {
  static constexpr u32 umod = u32(mod);
  static_assert(umod < u32(1) << 31);
  u32 val;

  static modint raw(u32 v) {
    modint x;
    x.val = v;
    return x;
  }
  constexpr modint() : val(0) {}
  constexpr modint(u32 x) : val(x % umod) {}
  constexpr modint(u64 x) : val(x % umod) {}
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
  constexpr modint(ll x) : val((x %= mod) < 0 ? x + mod : x){};
  bool operator<(const modint &other) const { return val < other.val; }
  modint &operator+=(const modint &p) {
    if ((val += p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator-=(const modint &p) {
    if ((val += umod - p.val) >= umod) val -= umod;
    return *this;
  }
  modint &operator*=(const modint &p) {
    val = u64(val) * p.val % umod;
    return *this;
  }
  modint &operator/=(const modint &p) {
    *this *= p.inverse();
    return *this;
  }
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator-(const modint &p) const { return modint(*this) -= p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
  modint operator/(const modint &p) const { return modint(*this) /= p; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
  modint inverse() const {
    int a = val, b = mod, u = 1, v = 0, t;
    while (b > 0) {
      t = a / b;
      swap(a -= t * b, b), swap(u -= t * v, v);
    }
    return modint(u);
  }
  modint pow(ll n) const {
    assert(n >= 0);
    modint ret(1), mul(val);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }
  static constexpr int get_mod() { return mod; }
};

using modint998 = modint<998244353>;

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
  vc<int> vc_deg, vc_indeg, vc_outdeg;
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

  vc<int> new_idx;
  vc<bool> used_e;

  // G における頂点 V[i] が、新しいグラフで i になるようにする
  // {G, es}
  // sum(deg(v)) の計算量になっていて、
  // 新しいグラフの n+m より大きい可能性があるので注意
  Graph<T, directed> rearrange(vc<int> V, bool keep_eid = 0) {
    if (len(new_idx) != N) new_idx.assign(N, -1);
    int n = len(V);
    FOR(i, n) new_idx[V[i]] = i;
    Graph<T, directed> G(n);
    vc<int> history;
    FOR(i, n) {
      for (auto &&e: (*this)[V[i]]) {
        if (len(used_e) <= e.id) used_e.resize(e.id + 1);
        if (used_e[e.id]) continue;
        int a = e.frm, b = e.to;
        if (new_idx[a] != -1 && new_idx[b] != -1) {
          history.eb(e.id);
          used_e[e.id] = 1;
          int eid = (keep_eid ? e.id : -1);
          G.add(new_idx[a], new_idx[b], e.cost, eid);
        }
      }
    }
    FOR(i, n) new_idx[V[i]] = -1;
    for (auto &&eid: history) used_e[eid] = 0;
    G.build();
    return G;
  }
};

int det_mod(vvc<int> A, int mod) {
  const int n = len(A);
  ll det = 1;
  FOR(i, n) {
    FOR(j, i, n) {
      if (A[j][i] == 0) continue;
      if (i != j) { swap(A[i], A[j]), det = mod - det; }
      break;
    }
    FOR(j, i + 1, n) {
      while (A[i][i] != 0) {
        ll c = mod - A[j][i] / A[i][i];
        FOR_R(k, i, n) { A[j][k] = (A[j][k] + A[i][k] * c) % mod; }
        swap(A[i], A[j]), det = mod - det;
      }
      swap(A[i], A[j]), det = mod - det;
    }
  }
  FOR(i, n) det = det * A[i][i] % mod;
  return det % mod;
}

template <typename mint>
mint det(vvc<mint> &A) {
  const int n = len(A);
  vv(int, B, n, n);
  FOR(i, n) FOR(j, n) B[i][j] = A[i][j].val;
  return det_mod(B, mint::get_mod());
}

/*
ひとつ選んだ辺から始めて全ての辺を通る closed walk を数える.
多重辺は vc<int>(eid) で渡す，なければすべて 1. e.cost は参照しない.
辺はラベル付きで考える. 多重辺を同一視する場合などは後で階乗で割ること.
O(N^2+NM) （ + 最後に重複度の階乗をかける）．
*/
template <typename mint, typename GT>
mint BEST_theorem(GT G, vc<int> edge_multiplicity = {}) {
  static_assert(GT::is_directed);
  int N = G.N, M = G.M;
  if (M == 0) return 0;
  if (edge_multiplicity.empty()) edge_multiplicity.assign(M, 1);
  vc<int> vs;
  for (auto &e: G.edges) {
    if (edge_multiplicity[e.id] == 0) continue;
    vs.eb(e.frm), vs.eb(e.to);
  }

  UNIQUE(vs);
  G = G.rearrange(vs, true);
  N = G.N;

  vc<int> indeg(N), outdeg(N);
  vv(mint, mat, N - 1, N - 1);
  for (auto &e: G.edges) {
    int a = e.frm, b = e.to, x = edge_multiplicity[e.id];
    outdeg[a] += x, indeg[b] += x;
    if (a < N - 1 && b < N - 1) mat[a][b] -= x;
    if (a < N - 1) mat[a][a] += x;
  }
  FOR(v, N) if (indeg[v] != outdeg[v]) return 0;
  mint d = det<mint>(mat);
  for (auto &x: outdeg) { d *= fact<mint>(x - 1); }
  return d;
}

using mint = modint998;

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
  mint ANS = BEST_theorem<mint>(G);
  printf("%d\n", ANS.val);
}

signed main() { solve(); }
