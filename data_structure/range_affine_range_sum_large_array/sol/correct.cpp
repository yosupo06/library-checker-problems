#include <vector>
#include <tuple>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <cassert>
#include <functional>

using namespace std;

using ll = long long;
using u8 = uint8_t;
using u16 = uint16_t;
using u32 = uint32_t;
using u64 = uint64_t;

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

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

// Q*2logN 程度必要
template <typename ActedMonoid, bool PERSISTENT>
struct Dynamic_Lazy_SegTree {
  using AM = ActedMonoid;
  using MX = typename AM::Monoid_X;
  using MA = typename AM::Monoid_A;
  using X = typename AM::X;
  using A = typename AM::A;
  using F = function<X(ll, ll)>;
  F default_prod;

  struct Node {
    Node *l, *r;
    X x;
    A lazy;
  };

  const int NODES;
  const ll L0, R0;
  Node *pool;
  int pid;
  using np = Node *;

  Dynamic_Lazy_SegTree(
      int NODES, ll L0, ll R0, F default_prod = [](ll, ll) -> X { return MX::unit(); })
      : default_prod(default_prod), NODES(NODES), L0(L0), R0(R0), pid(0) {
    pool = new Node[NODES];
  }
  ~Dynamic_Lazy_SegTree() { delete[] pool; }

  np new_root() { return new_node(L0, R0); }

  np new_node(const X x) {
    assert(pid < NODES);
    pool[pid].l = pool[pid].r = nullptr;
    pool[pid].x = x;
    pool[pid].lazy = MA::unit();
    return &(pool[pid++]);
  }

  np new_node(ll l, ll r) { return new_node(default_prod(l, r)); }
  np new_node() { return new_node(L0, R0); }

  X prod(np root, ll l, ll r) {
    if (l == r || !root) return MX::unit();
    assert(pid && L0 <= l && l < r && r <= R0);
    X x = MX::unit();
    prod_rec(root, L0, R0, l, r, x, MA::unit());
    return x;
  }

  X prod_all(np root) { return prod(root, L0, R0); }

  np apply(np root, ll l, ll r, const A &a) {
    if (l == r) return root;
    assert(pid && L0 <= l && l < r && r <= R0);
    return apply_rec(root, L0, R0, l, r, a);
  }

private:
  np copy_node(np c) {
    if (!c || !PERSISTENT) return c;
    pool[pid].l = c->l, pool[pid].r = c->r;
    pool[pid].x = c->x;
    pool[pid].lazy = c->lazy;
    return &(pool[pid++]);
  }

  void prop(np c, ll l, ll r) {
    assert(r - l >= 2);
    ll m = (l + r) / 2;
    if (c->lazy == MA::unit()) return;
    c->l = (c->l ? copy_node(c->l) : new_node(l, m));
    c->l->x = AM::act(c->l->x, c->lazy, m - l);
    c->l->lazy = MA::op(c->l->lazy, c->lazy);
    c->r = (c->r ? copy_node(c->r) : new_node(m, r));
    c->r->x = AM::act(c->r->x, c->lazy, r - m);
    c->r->lazy = MA::op(c->r->lazy, c->lazy);
    c->lazy = MA::unit();
  }

  void prod_rec(np c, ll l, ll r, ll ql, ll qr, X &x, A lazy) {
    chmax(ql, l);
    chmin(qr, r);
    if (ql >= qr) return;
    if (!c) {
      x = MX::op(x, AM::act(default_prod(ql, qr), lazy, qr - ql));
      return;
    }
    if (l == ql && r == qr) {
      x = MX::op(x, AM::act(c->x, lazy, r - l));
      return;
    }
    ll m = (l + r) / 2;
    lazy = MA::op(c->lazy, lazy);
    prod_rec(c->l, l, m, ql, qr, x, lazy);
    prod_rec(c->r, m, r, ql, qr, x, lazy);
  }

  np apply_rec(np c, ll l, ll r, ll ql, ll qr, const A &a) {
    if (!c) c = new_node(l, r);
    chmax(ql, l);
    chmin(qr, r);
    if (ql >= qr) return c;
    if (l == ql && r == qr) {
      c = copy_node(c);
      c->x = AM::act(c->x, a, r - l);
      c->lazy = MA::op(c->lazy, a);
      return c;
    }
    prop(c, l, r);
    ll m = (l + r) / 2;
    c = copy_node(c);
    c->l = apply_rec(c->l, l, m, ql, qr, a);
    c->r = apply_rec(c->r, m, r, ql, qr, a);
    c->x = MX::op(c->l->x, c->r->x);
    return c;
  }
};

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
  constexpr modint(int x) : val((x %= mod) < 0 ? x + mod : x){};
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
  modint operator-() const { return modint::raw(val ? mod - val : u32(0)); }
  modint operator+(const modint &p) const { return modint(*this) += p; }
  modint operator-(const modint &p) const { return modint(*this) -= p; }
  modint operator*(const modint &p) const { return modint(*this) *= p; }
  bool operator==(const modint &p) const { return val == p.val; }
  bool operator!=(const modint &p) const { return val != p.val; }
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

template <typename E>
struct Monoid_Add {
  using X = E;
  using value_type = X;
  static constexpr X op(const X &x, const X &y) noexcept { return x + y; }
  static constexpr X inverse(const X &x) noexcept { return -x; }
  static constexpr X power(const X &x, ll n) noexcept { return X(n) * x; }
  static constexpr X unit() { return X(0); }
  static constexpr bool commute = true;
};

// op(F, G) = comp(G,F), F のあとで G
template <typename K>
struct Monoid_Affine {
  using F = pair<K, K>;
  using value_type = F;
  using X = value_type;
  static constexpr F op(const F &x, const F &y) noexcept { return F({x.first * y.first, x.second * y.first + y.second}); }
  static constexpr F inverse(const F &x) {
    auto [a, b] = x;
    a = K(1) / a;
    return {a, a * (-b)};
  }
  static constexpr K eval(const F &f, K x) noexcept { return f.first * x + f.second; }
  static constexpr F unit() { return {K(1), K(0)}; }
  static constexpr bool commute = false;
};

template <typename E>
struct ActedMonoid_Sum_Affine {
  using Monoid_X = Monoid_Add<E>;
  using Monoid_A = Monoid_Affine<E>;
  using X = typename Monoid_X::value_type;
  using A = typename Monoid_A::value_type;
  static constexpr X act(const X &x, const A &a, const ll &size) { return x * a.fi + E(size) * a.se; }
};

using mint = modint998;

int get() {
  int x;
  scanf("%d", &x);
  return x;
}

void solve() {
  int N = get(), Q = get();
  Dynamic_Lazy_SegTree<ActedMonoid_Sum_Affine<mint>, false> seg(60 * Q, 0, N);
  auto root = seg.new_root();

  FOR(Q) {
    int t = get(), l = get(), r = get();
    if (t == 0) {
      int b = get(), c = get();
      root = seg.apply(root, l, r, {b, c});
    }
    if (t == 1) {
      mint ANS = seg.prod(root, l, r);
      printf("%d\n", ANS.val);
    }
  }
}

signed main() { solve(); }
