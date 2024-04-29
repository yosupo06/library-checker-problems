/**
 * date   : 2024-04-29 15:27:21
 * author : Nyaan
 */

#define NDEBUG


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





using namespace std;




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
  constexpr LazyMontgomeryModInt(const int64_t &b)
      : a(reduce(u64(b % mod + mod) * n2)){};

  static constexpr u32 reduce(const u64 &b) {
    return (b + u64(u32(b) * u32(-r)) * mod) >> 32;
  }

  constexpr mint &operator+=(const mint &b) {
    if (i32(a += b.a - 2 * mod) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator-=(const mint &b) {
    if (i32(a -= b.a) < 0) a += 2 * mod;
    return *this;
  }

  constexpr mint &operator*=(const mint &b) {
    a = reduce(u64(a) * b.a);
    return *this;
  }

  constexpr mint &operator/=(const mint &b) {
    *this *= b.inverse();
    return *this;
  }

  constexpr mint operator+(const mint &b) const { return mint(*this) += b; }
  constexpr mint operator-(const mint &b) const { return mint(*this) -= b; }
  constexpr mint operator*(const mint &b) const { return mint(*this) *= b; }
  constexpr mint operator/(const mint &b) const { return mint(*this) /= b; }
  constexpr bool operator==(const mint &b) const {
    return (a >= mod ? a - mod : a) == (b.a >= mod ? b.a - mod : b.a);
  }
  constexpr bool operator!=(const mint &b) const {
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

  friend ostream &operator<<(ostream &os, const mint &b) {
    return os << b.get();
  }

  friend istream &operator>>(istream &is, mint &b) {
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


//


namespace DynamicRerootingImpl {
template <typename Point, Point (*rake)(const Point &, const Point &)>
struct SplayTreeforDashedEdge {
  struct Node {
    Node *l, *r, *p;
    Point key, sum;

    explicit Node(const Point &_key)
        : l(nullptr), r(nullptr), p(nullptr), key(_key), sum(_key) {}
  };

  SplayTreeforDashedEdge() {}

  using NP = Node *;

  void rotr(NP t) {
    NP x = t->p, y = x->p;
    if ((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void rotl(NP t) {
    NP x = t->p, y = x->p;
    if ((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void update(NP t) {
    t->sum = t->key;
    if (t->l) t->sum = rake(t->sum, t->l->sum);
    if (t->r) t->sum = rake(t->sum, t->r->sum);
  }

  NP get_right(NP t) {
    while (t->r) t = t->r;
    return t;
  }

  NP alloc(const Point &v) {
    auto t = new Node(v);
    update(t);
    return t;
  }

  void splay(NP t) {
    while (t->p) {
      NP q = t->p;
      if (!q->p) {
        if (q->l == t)
          rotr(t);
        else
          rotl(t);
      } else {
        NP r = q->p;
        if (r->l == q) {
          if (q->l == t)
            rotr(q), rotr(t);
          else
            rotl(t), rotr(t);
        } else {
          if (q->r == t)
            rotl(q), rotl(t);
          else
            rotr(t), rotl(t);
        }
      }
    }
  }

  NP insert(NP t, const Point &v) {
    if (not t) {
      t = alloc(v);
      return t;
    } else {
      NP cur = get_right(t), z = alloc(v);
      splay(cur);
      z->p = cur;
      cur->r = z;
      update(cur);
      splay(z);
      return z;
    }
  }

  NP erase(NP t) {
    splay(t);
    NP x = t->l, y = t->r;
    delete t;
    if (not x) {
      t = y;
      if (t) t->p = nullptr;
    } else if (not y) {
      t = x;
      t->p = nullptr;
    } else {
      x->p = nullptr;
      t = get_right(x);
      splay(t);
      t->r = y;
      y->p = t;
      update(t);
    }
    return t;
  }
};

template <typename Path, typename Point, typename Info,
          Path (*vertex)(const Info &),
          Path (*compress)(const Path &, const Path &),
          Point (*rake)(const Point &, const Point &),
          Point (*add_edge)(const Path &),
          Path (*add_vertex)(const Point &, const Info &)>
struct TopTree {
 private:
  struct Node {
    Node *l, *r, *p;
    Info info;
    Path key, sum, mus;
    typename SplayTreeforDashedEdge<Point, rake>::Node *light, *belong;
    bool rev;

    bool is_root() const { return not p or (p->l != this and p->r != this); }

    explicit Node(const Info _info)
        : l(nullptr),
          r(nullptr),
          p(nullptr),
          info(_info),
          light(nullptr),
          belong(nullptr),
          rev(false) {}
  };

 public:
  using NP = Node *;
  SplayTreeforDashedEdge<Point, rake> splay_tree;

 private:
  void toggle(NP t) {
    swap(t->l, t->r);
    swap(t->sum, t->mus);
    t->rev ^= true;
  }

  void rotr(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if ((x->l = t->r)) t->r->p = x;
    t->r = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

  void rotl(NP t) {
    NP x = t->p, y = x->p;
    push(x), push(t);
    if ((x->r = t->l)) t->l->p = x;
    t->l = x, x->p = t;
    update(x), update(t);
    if ((t->p = y)) {
      if (y->l == x) y->l = t;
      if (y->r == x) y->r = t;
    }
  }

 public:
  TopTree() : splay_tree{} {}

  void push(NP t) {
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void push_rev(NP t) {
    if (t->rev) {
      if (t->l) toggle(t->l);
      if (t->r) toggle(t->r);
      t->rev = false;
    }
  }

  void update(NP t) {
    Path key = t->light ? add_vertex(t->light->sum, t->info) : vertex(t->info);
    Path sum = key, mus = key;
    if (t->l) sum = compress(t->l->sum, sum), mus = compress(mus, t->l->mus);
    if (t->r) sum = compress(sum, t->r->sum), mus = compress(t->r->mus, mus);
    t->key = key, t->sum = sum, t->mus = mus;
  }

  void splay(NP t) {
    push(t);
    {
      NP rot = t;
      while (not rot->is_root()) rot = rot->p;
      t->belong = rot->belong;
      if (t != rot) rot->belong = nullptr;
    }
    while (not t->is_root()) {
      NP q = t->p;
      if (q->is_root()) {
        push_rev(q), push_rev(t);
        if (q->l == t)
          rotr(t);
        else
          rotl(t);
      } else {
        NP r = q->p;
        push_rev(r), push_rev(q), push_rev(t);
        if (r->l == q) {
          if (q->l == t)
            rotr(q), rotr(t);
          else
            rotl(t), rotr(t);
        } else {
          if (q->r == t)
            rotl(q), rotl(t);
          else
            rotr(t), rotl(t);
        }
      }
    }
  }

  NP expose(NP t) {
    NP rp = nullptr;
    for (NP cur = t; cur; cur = cur->p) {
      splay(cur);
      if (cur->r) {
        cur->light = splay_tree.insert(cur->light, add_edge(cur->r->sum));
        cur->r->belong = cur->light;
      }
      cur->r = rp;
      if (cur->r) {
        splay_tree.splay(cur->r->belong);
        push(cur->r);
        cur->light = splay_tree.erase(cur->r->belong);
      }
      update(cur);
      rp = cur;
    }
    splay(t);
    return rp;
  }

  void link(NP child, NP parent) {
    expose(parent);
    expose(child);
    child->p = parent;
    parent->r = child;
    update(parent);
  }

  void cut(NP child) {
    expose(child);
    NP parent = child->l;
    child->l = nullptr;
    parent->p = nullptr;
    update(child);
  }

  void evert(NP t) {
    expose(t);
    toggle(t);
    push(t);
  }

  NP alloc(const Info &info) {
    NP t = new Node(info);
    update(t);
    return t;
  }

  bool is_connected(NP u, NP v) {
    expose(u), expose(v);
    return u == v or u->p;
  }

  NP lca(NP u, NP v) {
    if (not is_connected(u, v)) return nullptr;
    expose(u);
    return expose(v);
  }

  void set_key(NP t, const Info &v) {
    expose(t);
    t->info = v;
    update(t);
  }

  // u を根とする sum
  Path query(NP u) {
    evert(u);
    return u->sum;
  }

  // root を根, u を部分木の根とする sum
  Path query_subtree(NP root, NP u) {
    evert(root);
    expose(u);
    NP l = u->l;
    u->l = nullptr;
    update(u);
    auto ret = u->sum;
    u->l = l;
    update(u);
    return ret;
  }
};

template <typename Path, typename Point, typename Info,
          Path (*vertex)(const Info &),
          Path (*compress)(const Path &, const Path &),
          Point (*rake)(const Point &, const Point &),
          Point (*Add_edge)(const Path &),
          Path (*add_vertex)(const Point &, const Info &)>
struct DynamicRerooting {
  int n;
  TopTree<Path, Point, Info, vertex, compress, rake, Add_edge, add_vertex> tt;
  using NP = typename decltype(tt)::NP;
  vector<NP> vs;

  DynamicRerooting(int _n, const vector<Info> &info) : n(_n), vs(n) {
    for (int i = 0; i < n; i++) vs[i] = tt.alloc(info[i]);
  }
  // u-v 間に辺を追加
  void add_edge(int u, int v) {
    tt.evert(vs[u]);
    tt.link(vs[u], vs[v]);
  }
  // u-v 間の辺を削除
  void del_edge(int u, int v) {
    tt.evert(vs[u]);
    tt.cut(vs[v]);
  }
  // 頂点 u の情報を取得
  Info get_info(int u) { return vs[u]->info; }
  // 頂点 u の情報を設定
  void set_info(int u, const Info &info) { tt.set_key(vs[u], info); }
  // 頂点 u を根とするクエリ
  Path query(int u) { return tt.query(vs[u]); }
  // 頂点 root を根, 頂点 u を部分木の根とするクエリ
  Path query_subtree(int root, int u) {
    return tt.query_subtree(vs[root], vs[u]);
  }
};

}  // namespace DynamicRerootingImpl

using DynamicRerootingImpl::DynamicRerooting;
using DynamicRerootingImpl::TopTree;

/*
struct Path {

};
struct Point {

};
struct Info {

};
Path vertex(const Info &i) {

}
Path compress(const Path &p, const Path &c) {

}
Point rake(const Point &a, const Point &b) {

}
Point add_edge(const Path &a) {

}
Path add_vertex(const Point &a, const Info &i) {

}

using DR = DynamicRerooting<Path, Point, Info, vertex, compress, rake, add_edge,
                            add_vertex>;
*/


//
using mint = LazyMontgomeryModInt<998244353>;

struct Path {
  mint a, b, s, x;
};
struct Point {
  mint s, x;
};
struct Info {
  bool vertex;
  mint x, y;
};
Path vertex(const Info &i) {
  if (i.vertex) return {1, 0, i.x, 1};
  return {i.x, i.y, 0, 0};
}
Path compress(const Path &p, const Path &c) {
  return {p.a * c.a, p.a * c.b + p.b, p.s + p.a * c.s + p.b * c.x, p.x + c.x};
}
Point rake(const Point &a, const Point &b) { return {a.s + b.s, a.x + b.x}; }
Point add_edge(const Path &a) { return {a.s, a.x}; }
Path add_vertex(const Point &a, const Info &i) {
  if (i.vertex) return {1, 0, a.s + i.x, a.x + 1};
  return {i.x, i.y, a.s * i.x + a.x * i.y, a.x};
}

using DR = DynamicRerooting<Path, Point, Info, vertex, compress, rake, add_edge,
                            add_vertex>;

int main() {
  int N, Q;
  rd(N, Q);
  vector<int> A(N);
  for (auto &x : A) rd(x);
  vector<int> U(N - 1), V(N - 1), B(N - 1), C(N - 1);
  for (int i = 0; i < N - 1; i++) rd(U[i], V[i], B[i], C[i]);

  vector<Info> info(2 * N - 1);
  for (int i = 0; i < N; i++) info[i] = {true, A[i], 0};
  for (int i = 0; i < N - 1; i++) info[N + i] = {false, B[i], C[i]};

  DR dr{2 * N - 1, info};
  for (int i = 0; i < N - 1; i++) {
    dr.add_edge(N + i, U[i]), dr.add_edge(N + i, V[i]);
  }

  while (Q--) {
    int cmd, i, x;
    rd(cmd, i, x);
    if (cmd == 0) {
      dr.set_info(i, {true, x, 0});
    } else {
      int y;
      rd(y);
      dr.set_info(N + i, {false, x, y});
    }
    int r;
    rd(r);
    wtn(dr.query(r).s.get());
  }
}
