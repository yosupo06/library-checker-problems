#include <algorithm>
#include <array>
#include <bitset>
#include <cassert>
#include <cctype>
#include <cfenv>
#include <cfloat>
#include <chrono>
#include <cinttypes>
#include <climits>
#include <cmath>
#include <complex>
#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <deque>
#include <fstream>
#include <functional>
#include <initializer_list>
#include <iomanip>
#include <ios>
#include <iostream>
#include <istream>
#include <iterator>
#include <limits>
#include <list>
#include <map>
#include <memory>
#include <new>
#include <numeric>
#include <ostream>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <stack>
#include <streambuf>
#include <string>
#include <tuple>
#include <type_traits>
#include <typeinfo>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

using namespace std;

namespace internal {
template <typename T>
using is_broadly_integral =
    typename conditional_t<is_integral_v<T> || is_same_v<T, __int128_t> ||
                               is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_signed =
    typename conditional_t<is_signed_v<T> || is_same_v<T, __int128_t>,
                           true_type, false_type>::type;

template <typename T>
using is_broadly_unsigned =
    typename conditional_t<is_unsigned_v<T> || is_same_v<T, __uint128_t>,
                           true_type, false_type>::type;

#define ENABLE_VALUE(x) \
  template <typename T> \
  constexpr bool x##_v = x<T>::value;

ENABLE_VALUE(is_broadly_integral);
ENABLE_VALUE(is_broadly_signed);
ENABLE_VALUE(is_broadly_unsigned);
#undef ENABLE_VALUE

#define ENABLE_HAS_TYPE(var)                                   \
  template <class, class = void>                               \
  struct has_##var : false_type {};                            \
  template <class T>                                           \
  struct has_##var<T, void_t<typename T::var>> : true_type {}; \
  template <class T>                                           \
  constexpr auto has_##var##_v = has_##var<T>::value;

#define ENABLE_HAS_VAR(var)                                     \
  template <class, class = void>                                \
  struct has_##var : false_type {};                             \
  template <class T>                                            \
  struct has_##var<T, void_t<decltype(T::var)>> : true_type {}; \
  template <class T>                                            \
  constexpr auto has_##var##_v = has_##var<T>::value;

}  // namespace internal

namespace fastio {
static constexpr int SZ = 1 << 17;
static constexpr int offset = 64;
char inbuf[SZ], outbuf[SZ];
int in_left = 0, in_right = 0, out_right = 0;

struct Pre {
  char num[40000];
  constexpr Pre() : num() {
    for (int i = 0; i < 10000; i++) {
      int n = i;
      for (int j = 3; j >= 0; j--) {
        num[i * 4 + j] = n % 10 + '0';
        n /= 10;
      }
    }
  }
} constexpr pre;

void load() {
  int len = in_right - in_left;
  memmove(inbuf, inbuf + in_left, len);
  in_right = len + fread(inbuf + len, 1, SZ - len, stdin);
  in_left = 0;
}
void flush() {
  fwrite(outbuf, 1, out_right, stdout);
  out_right = 0;
}
void skip_space() {
  if (in_left + offset > in_right) load();
  while (inbuf[in_left] <= ' ') in_left++;
}

void single_read(char& c) {
  if (in_left + offset > in_right) load();
  skip_space();
  c = inbuf[in_left++];
}
void single_read(string& S) {
  skip_space();
  while (true) {
    if (in_left == in_right) load();
    int i = in_left;
    for (; i != in_right; i++) {
      if (inbuf[i] <= ' ') break;
    }
    copy(inbuf + in_left, inbuf + i, back_inserter(S));
    in_left = i;
    if (i != in_right) break;
  }
}
template <typename T,
          enable_if_t<internal::is_broadly_integral_v<T>>* = nullptr>
void single_read(T& x) {
  if (in_left + offset > in_right) load();
  skip_space();
  char c = inbuf[in_left++];
  [[maybe_unused]] bool minus = false;
  if constexpr (internal::is_broadly_signed_v<T>) {
    if (c == '-') minus = true, c = inbuf[in_left++];
  }
  x = 0;
  while (c >= '0') {
    x = x * 10 + (c & 15);
    c = inbuf[in_left++];
  }
  if constexpr (internal::is_broadly_signed_v<T>) {
    if (minus) x = -x;
  }
}
void rd() {}
template <typename Head, typename... Tail>
void rd(Head& head, Tail&... tail) {
  single_read(head);
  rd(tail...);
}

void single_write(const char& c) {
  if (out_right > SZ - offset) flush();
  outbuf[out_right++] = c;
}
void single_write(const bool& b) {
  if (out_right > SZ - offset) flush();
  outbuf[out_right++] = b ? '1' : '0';
}
void single_write(const string& S) {
  flush(), fwrite(S.data(), 1, S.size(), stdout);
}
void single_write(const char* p) { flush(), fwrite(p, 1, strlen(p), stdout); }
template <typename T,
          enable_if_t<internal::is_broadly_integral_v<T>>* = nullptr>
void single_write(const T& _x) {
  if (out_right > SZ - offset) flush();
  if (_x == 0) {
    outbuf[out_right++] = '0';
    return;
  }
  T x = _x;
  if constexpr (internal::is_broadly_signed_v<T>) {
    if (x < 0) outbuf[out_right++] = '-', x = -x;
  }
  constexpr int buffer_size = sizeof(T) * 10 / 4;
  char buf[buffer_size];
  int i = buffer_size;
  while (x >= 10000) {
    i -= 4;
    memcpy(buf + i, pre.num + (x % 10000) * 4, 4);
    x /= 10000;
  }
  if (x < 100) {
    if (x < 10) {
      outbuf[out_right] = '0' + x;
      ++out_right;
    } else {
      uint32_t q = (uint32_t(x) * 205) >> 11;
      uint32_t r = uint32_t(x) - q * 10;
      outbuf[out_right] = '0' + q;
      outbuf[out_right + 1] = '0' + r;
      out_right += 2;
    }
  } else {
    if (x < 1000) {
      memcpy(outbuf + out_right, pre.num + (x << 2) + 1, 3);
      out_right += 3;
    } else {
      memcpy(outbuf + out_right, pre.num + (x << 2), 4);
      out_right += 4;
    }
  }
  memcpy(outbuf + out_right, buf + i, buffer_size - i);
  out_right += buffer_size - i;
}
void wt() {}
template <typename Head, typename... Tail>
void wt(const Head& head, const Tail&... tail) {
  single_write(head);
  wt(std::forward<const Tail>(tail)...);
}
template <typename... Args>
void wtn(const Args&... x) {
  wt(std::forward<const Args>(x)...);
  wt('\n');
}

struct Dummy {
  Dummy() { atexit(flush); }
} dummy;

}  // namespace fastio
using fastio::rd;
using fastio::skip_space;
using fastio::wt;
using fastio::wtn;

//

template <uint32_t mod>
struct LazyMontgomeryModInt {
  using mint = LazyMontgomeryModInt;
  using i32 = int32_t;
  using u32 = uint32_t;
  using u64 = uint64_t;

  static constexpr u32 get_r() {
    u32 ret = mod;
    for (i32 i = 0; i < 4; ++i) ret *= 2 - mod * ret;
    return ret;
  }

  static constexpr u32 r = get_r();
  static constexpr u32 n2 = -u64(mod) % mod;
  static_assert(mod < (1 << 30), "invalid, mod >= 2 ^ 30");
  static_assert((mod & 1) == 1, "invalid, mod % 2 == 0");
  static_assert(r * mod == 1, "this code has bugs.");

  u32 a;

  constexpr LazyMontgomeryModInt() : a(0) {}
  constexpr LazyMontgomeryModInt(const int64_t& b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64& b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint& operator+=(const mint& b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint& operator-=(const mint& b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint& operator*=(const mint& b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint& operator/=(const mint& b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint& b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint& b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint& b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint& b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint& b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint& b) const {
    return (a >= mod ? a - mod : a) != (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr mint operator-() const { return mint() - mint(*this); }
  constexpr mint operator+() const { return mint(*this); }

  constexpr mint pow(u64 n) const {
    mint ret(1), mul(*this);
    while (n > 0) {
      if (n & 1) ret *= mul;
      mul *= mul;
      n >>= 1;
    }
    return ret;
  }

  constexpr mint inverse() const {
    int x = get(), y = mod, u = 1, v = 0, t = 0, tmp = 0;
    while (y > 0) {
      t = x / y;
      x -= t * y, u -= t * v;
      tmp = x, x = y, y = tmp;
      tmp = u, u = v, v = tmp;
    }
    return mint{u};
  }

  friend ostream& operator<<(ostream& os, const mint& b) {
    return os << b.get();
  }

  friend istream& operator>>(istream& is, mint& b) {
    int64_t t;
    is >> t;
    b = LazyMontgomeryModInt<mod>(t);
    return (is);
  }

  constexpr u32 get() const {
    u32 ret = reduce(a);
    return ret >= mod ? ret - mod : ret;
  }

  static constexpr u32 get_mod() { return mod; }
};

using namespace std;

template <typename T>
struct edge {
  int src, to;
  T cost;

  edge(int _to, T _cost) : src(-1), to(_to), cost(_cost) {}
  edge(int _src, int _to, T _cost) : src(_src), to(_to), cost(_cost) {}

  edge& operator=(const int& x) {
    to = x;
    return *this;
  }

  operator int() const { return to; }
};
template <typename T>
using Edges = vector<edge<T>>;
template <typename T>
using WeightedGraph = vector<Edges<T>>;
using UnweightedGraph = vector<vector<int>>;

/**
 * @brief グラフテンプレート
 * @docs docs/graph/graph-template.md
 */

template <typename T>
vector<vector<T>> rooted_tree(const vector<vector<T>>& g, int root = 0) {
  int N = (int)g.size();
  vector<vector<T>> rg(N);
  vector<char> v(N, false);
  v[root] = true;
  queue<int> que;
  que.emplace(root);
  while (!que.empty()) {
    auto p = que.front();
    que.pop();
    for (auto& e : g[p]) {
      if (v[e] == false) {
        v[e] = true;
        que.push(e);
        rg[p].push_back(e);
      }
    }
  }
  return rg;
}

/**
 * @brief 根付き木・逆辺からなる木への変換
 */

template <typename G>
struct HeavyLightDecomposition {
 private:
  void dfs_sz(int cur) {
    size[cur] = 1;
    for (auto& dst : g[cur]) {
      if (dst == par[cur]) {
        if (g[cur].size() >= 2 && int(dst) == int(g[cur][0]))
          swap(g[cur][0], g[cur][1]);
        else
          continue;
      }
      depth[dst] = depth[cur] + 1;
      par[dst] = cur;
      dfs_sz(dst);
      size[cur] += size[dst];
      if (size[dst] > size[g[cur][0]]) {
        swap(dst, g[cur][0]);
      }
    }
  }

  void dfs_hld(int cur) {
    down[cur] = id++;
    for (auto dst : g[cur]) {
      if (dst == par[cur]) continue;
      nxt[dst] = (int(dst) == int(g[cur][0]) ? nxt[cur] : int(dst));
      dfs_hld(dst);
    }
    up[cur] = id;
  }

  // [u, v)
  vector<pair<int, int>> ascend(int u, int v) const {
    vector<pair<int, int>> res;
    while (nxt[u] != nxt[v]) {
      res.emplace_back(down[u], down[nxt[u]]);
      u = par[nxt[u]];
    }
    if (u != v) res.emplace_back(down[u], down[v] + 1);
    return res;
  }

  // (u, v]
  vector<pair<int, int>> descend(int u, int v) const {
    if (u == v) return {};
    if (nxt[u] == nxt[v]) return {{down[u] + 1, down[v]}};
    auto res = descend(u, par[nxt[v]]);
    res.emplace_back(down[nxt[v]], down[v]);
    return res;
  }

 public:
  G& g;
  int root, id;
  vector<int> size, depth, down, up, nxt, par;
  HeavyLightDecomposition(G& _g, int _root = 0)
      : g(_g),
        root(_root),
        id(0),
        size(g.size(), 0),
        depth(g.size(), 0),
        down(g.size(), -1),
        up(g.size(), -1),
        nxt(g.size(), root),
        par(g.size(), root) {
    dfs_sz(root);
    dfs_hld(root);
  }

  pair<int, int> idx(int i) const { return make_pair(down[i], up[i]); }

  template <typename F>
  void path_query(int u, int v, bool vertex, const F& f) {
    int l = lca(u, v);
    for (auto&& [a, b] : ascend(u, l)) {
      int s = a + 1, t = b;
      s > t ? f(t, s) : f(s, t);
    }
    if (vertex) f(down[l], down[l] + 1);
    for (auto&& [a, b] : descend(l, v)) {
      int s = a, t = b + 1;
      s > t ? f(t, s) : f(s, t);
    }
  }

  template <typename F>
  void path_noncommutative_query(int u, int v, bool vertex, const F& f) {
    int l = lca(u, v);
    for (auto&& [a, b] : ascend(u, l)) f(a + 1, b);
    if (vertex) f(down[l], down[l] + 1);
    for (auto&& [a, b] : descend(l, v)) f(a, b + 1);
  }

  template <typename F>
  void subtree_query(int u, bool vertex, const F& f) {
    f(down[u] + int(!vertex), up[u]);
  }

  int lca(int a, int b) {
    while (nxt[a] != nxt[b]) {
      if (down[a] < down[b]) swap(a, b);
      a = par[nxt[a]];
    }
    return depth[a] < depth[b] ? a : b;
  }

  int dist(int a, int b) { return depth[a] + depth[b] - depth[lca(a, b)] * 2; }
};

/**
 * @brief Heavy Light Decomposition(重軽分解)
 * @docs docs/tree/heavy-light-decomposition.md
 */

namespace StaticTopTreeVertexBasedImpl {

enum Type { Vertex, Compress, Rake, Add_Edge, Add_Vertex };

template <typename G>
struct StaticTopTreeVertexBased {
  const HeavyLightDecomposition<G>& hld;
  vector<vector<int>> g;
  int root;     // 元の木の root
  int tt_root;  // top tree の root
  vector<int> P, L, R;
  vector<Type> T;

  StaticTopTreeVertexBased(const HeavyLightDecomposition<G>& _hld) : hld(_hld) {
    root = hld.root;
    g = rooted_tree(hld.g, root);
    int n = g.size();
    P.resize(n, -1), L.resize(n, -1), R.resize(n, -1);
    T.resize(n, Type::Vertex);
    build();
  }

 private:
  int add(int l, int r, Type t) {
    if (t == Type::Compress or t == Type::Rake) {
      assert(l != -1 and r != -1);
    }
    if (t == Type::Add_Edge) {
      assert(l != -1 and r == -1);
    }
    assert(t != Type::Vertex and t != Type::Add_Vertex);
    int k = P.size();
    P.push_back(-1), L.push_back(l), R.push_back(r), T.push_back(t);
    if (l != -1) P[l] = k;
    if (r != -1) P[r] = k;
    return k;
  }
  int add2(int k, int l, int r, Type t) {
    assert(k < (int)g.size());
    assert(t == Type::Vertex or t == Type::Add_Vertex);
    if (t == Type::Vertex) {
      assert(l == -1 and r == -1);
    } else {
      assert(l != -1 and r == -1);
    }
    P[k] = -1, L[k] = l, R[k] = r, T[k] = t;
    if (l != -1) P[l] = k;
    if (r != -1) P[r] = k;
    return k;
  }
  pair<int, int> merge(const vector<pair<int, int>>& a, Type t) {
    assert(!a.empty());
    if (a.size() == 1) return a[0];
    int sum_s = 0;
    for (auto& [_, s] : a) sum_s += s;
    vector<pair<int, int>> b, c;
    for (auto& [i, s] : a) {
      (sum_s > s ? b : c).emplace_back(i, s);
      sum_s -= s * 2;
    }
    auto [i, si] = merge(b, t);
    auto [j, sj] = merge(c, t);
    return {add(i, j, t), si + sj};
  }
  pair<int, int> compress(int i) {
    vector<pair<int, int>> chs;
    while (true) {
      chs.push_back(add_vertex(i));
      if (g[i].empty()) break;
      i = g[i][0];
    }
    return merge(chs, Type::Compress);
  }
  pair<int, int> rake(int i) {
    vector<pair<int, int>> chs;
    for (int j = 1; j < (int)g[i].size(); j++) chs.push_back(add_edge(g[i][j]));
    if (chs.empty()) return {-1, 0};
    return merge(chs, Type::Rake);
  }
  pair<int, int> add_edge(int i) {
    auto [j, sj] = compress(i);
    return {add(j, -1, Type::Add_Edge), sj};
  }
  pair<int, int> add_vertex(int i) {
    auto [j, sj] = rake(i);
    return {add2(i, j, -1, j == -1 ? Type::Vertex : Type::Add_Vertex), sj + 1};
  }
  void build() {
    auto [i, n] = compress(root);
    assert((int)g.size() == n);
    tt_root = i;
  }
};

template <typename G, typename Path, typename Point, typename Vertex,
          typename Compress, typename Rake, typename Add_edge,
          typename Add_vertex>
struct DPonStaticTopTreeVertexBased {
  const StaticTopTreeVertexBased<G> tt;
  vector<Path> path;
  vector<Point> point;
  const Vertex vertex;
  const Compress compress;
  const Rake rake;
  const Add_edge add_edge;
  const Add_vertex add_vertex;

  DPonStaticTopTreeVertexBased(const HeavyLightDecomposition<G>& hld,
                               const Vertex& _vertex, const Compress& _compress,
                               const Rake& _rake, const Add_edge& _add_edge,
                               const Add_vertex& _add_vertex)
      : tt(hld),
        vertex(_vertex),
        compress(_compress),
        rake(_rake),
        add_edge(_add_edge),
        add_vertex(_add_vertex) {
    int n = tt.P.size();
    path.resize(n), point.resize(n);
    dfs(tt.tt_root);
  }

  Path get() { return path[tt.tt_root]; }
  void update(int k) {
    while (k != -1) _update(k), k = tt.P[k];
  }

 private:
  void _update(int k) {
    if (tt.T[k] == Type::Vertex) {
      path[k] = vertex(k);
    } else if (tt.T[k] == Type::Compress) {
      path[k] = compress(path[tt.L[k]], path[tt.R[k]]);
    } else if (tt.T[k] == Type::Rake) {
      point[k] = rake(point[tt.L[k]], point[tt.R[k]]);
    } else if (tt.T[k] == Type::Add_Edge) {
      point[k] = add_edge(path[tt.L[k]]);
    } else {
      path[k] = add_vertex(point[tt.L[k]], k);
    }
  }

  void dfs(int k) {
    if (tt.L[k] != -1) dfs(tt.L[k]);
    if (tt.R[k] != -1) dfs(tt.R[k]);
    _update(k);
  }
};

}  // namespace StaticTopTreeVertexBasedImpl

using StaticTopTreeVertexBasedImpl::DPonStaticTopTreeVertexBased;
using StaticTopTreeVertexBasedImpl::StaticTopTreeVertexBased;

/**
 * @brief Static Top Tree
 */

//
using mint = LazyMontgomeryModInt<998244353>;

#define rep(i, n) for (int i = 0; i < (n); i++)
#define each(x, v) for (auto&& x : v)

struct Path {
  mint a, b, s, x;
};
struct Point {
  mint s, x;
};
vector<mint> calc(int N, int Q, vector<int> A, vector<int> U, vector<int> V,
                  vector<int> B, vector<int> C, vector<int> cmd, vector<int> I,
                  vector<int> X, vector<int> Y) {
  vector<vector<int>> g(2 * N - 1);
  rep(e, N - 1) {
    g[N + e].push_back(U[e]), g[U[e]].push_back(N + e);
    g[N + e].push_back(V[e]), g[V[e]].push_back(N + e);
  }
  auto vertex = [&](int i) -> Path {
    if (i < N) return {1, 0, A[i], 1};
    int e = i - N;
    return {B[e], C[e], 0, 0};
  };
  auto compress = [&](const Path& p, const Path& c) -> Path {
    return {p.a * c.a, p.a * c.b + p.b, p.s + p.a * c.s + p.b * c.x, p.x + c.x};
  };
  auto rake = [&](const Point& a, const Point& b) -> Point {
    return {a.s + b.s, a.x + b.x};
  };
  auto add_edge = [&](const Path& a) -> Point { return {a.s, a.x}; };
  auto add_vertex = [&](const Point& a, int i) -> Path {
    if (i < N) return {1, 0, a.s + A[i], a.x + 1};
    int e = i - N;
    return {B[e], C[e], a.s * B[e] + a.x * C[e], a.x};
  };

  HeavyLightDecomposition hld{g};
  DPonStaticTopTreeVertexBased<
      vector<vector<int>>, Path, Point, decltype(vertex), decltype(compress),
      decltype(rake), decltype(add_edge), decltype(add_vertex)>
      dp(hld, vertex, compress, rake, add_edge, add_vertex);

  vector<mint> ans(Q);
  rep(q, Q) {
    if (cmd[q] == 0) {
      A[I[q]] = X[q];
      dp.update(I[q]);
    } else {
      B[I[q]] = X[q], C[I[q]] = Y[q];
      dp.update(N + I[q]);
    }
    ans[q] = dp.get().s;
  }
  return ans;
}

vector<mint> naive(int N, int Q, vector<int> A, vector<int> U, vector<int> V,
                   vector<int> B, vector<int> C, vector<int> cmd, vector<int> I,
                   vector<int> X, vector<int> Y) {
  vector<mint> ans(Q);

  rep(q, Q) {
    if (cmd[q] == 0) {
      A[I[q]] = X[q];
    } else {
      B[I[q]] = X[q], C[I[q]] = Y[q];
    }
    vector<vector<pair<int, pair<mint, mint>>>> g(N);
    rep(i, N - 1) {
      g[U[i]].emplace_back(V[i], make_pair(B[i], C[i]));
      g[V[i]].emplace_back(U[i], make_pair(B[i], C[i]));
    }
    auto dfs = [&](auto rc, int c, int p) -> pair<mint, mint> {
      pair<mint, mint> res{0, 0};
      for (auto& dab : g[c]) {
        int d = dab.first;
        if (d == p) continue;
        auto [a, b] = dab.second;
        auto [x, n] = rc(rc, d, c);
        res.first += (x + A[d]) * a + b * (n + 1);
        res.second += n + 1;
      }
      return res;
    };
    ans[q] = dfs(dfs, 0, -1).first + A[0];
  }
  return ans;
}

int main() {
  // test();

  int N, Q;
  rd(N, Q);
  vector<int> A(N);
  for (auto& x : A) rd(x);
  vector<int> U(N - 1), V(N - 1), B(N - 1), C(N - 1);
  rep(i, N - 1) rd(U[i], V[i], B[i], C[i]);
  vector<int> cmd(Q), I(Q), X(Q), Y(Q, -1);
  rep(i, Q) {
    rd(cmd[i], I[i], X[i]);
    if (cmd[i] == 1) rd(Y[i]);
  }

  // auto an = naive(N, Q, A, U, V, B, C, cmd, I, X, Y);
  auto ac = calc(N, Q, A, U, V, B, C, cmd, I, X, Y);
  for (auto& x : ac) wtn(x.get());
}
