#include <vector>
#include <tuple>
#include <cstdio>
#include <cstdlib>
#include <cstdint>
#include <algorithm>
#include <numeric>
#include <cassert>

using namespace std;

using ll = long long;
using u32 = uint32_t;
using u64 = uint64_t;

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

#define FOR_subset(t, s) for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
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
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

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

// 常にほとんどの要素が unit であることが保証されるような動的セグ木
// したがって、default_prod の類は持たせられず、acted monoid も一般には扱えない
// 追加 N 回のときノード数 N 以下が保証される
template <typename Monoid, bool PERSISTENT>
struct Dynamic_SegTree_Sparse {
  using MX = Monoid;
  using X = typename MX::value_type;

  struct Node {
    ll idx;
    Node *l, *r;
    X prod, x;
  };
  const int NODES;
  const ll L0, R0;
  Node *pool;
  int pid;
  using np = Node *;
  vc<np> FREE;

  Dynamic_SegTree_Sparse(int NODES, ll L0, ll R0) : NODES(NODES), L0(L0), R0(R0), pid(0) { pool = new Node[NODES]; }
  ~Dynamic_SegTree_Sparse() { delete[] pool; }

  void free_subtree(np c) {
    auto dfs = [&](auto &dfs, np c) -> void {
      if (c->l) dfs(dfs, c->l);
      if (c->r) dfs(dfs, c->r);
      FREE.eb(c);
    };
    dfs(dfs, c);
  }

  np new_root() { return nullptr; }

  np new_node(ll idx, const X x) {
    if (!FREE.empty()) {
      np c = POP(FREE);
      c->idx = idx, c->l = c->r = nullptr;
      c->prod = c->x = x;
      return c;
    }
    assert(pid < NODES);
    pool[pid].idx = idx;
    pool[pid].l = pool[pid].r = nullptr;
    pool[pid].x = pool[pid].prod = x;
    return &(pool[pid++]);
  }

  X prod(np root, ll l, ll r) {
    assert(L0 <= l && l <= r && r <= R0);
    if (l == r) return MX::unit();
    X x = MX::unit();
    prod_rec(root, L0, R0, l, r, x);
    return x;
  }

  np set(np root, ll i, const X &x) {
    assert(L0 <= i && i < R0);
    return set_rec(root, L0, R0, i, x);
  }

  X get(np root, ll idx) {
    auto dfs = [&](auto &dfs, np c) -> X {
      if (!c) return Monoid::unit();
      if (idx == c->idx) return c->x;
      if (idx < (c->idx)) return dfs(dfs, c->l);
      return dfs(dfs, c->r);
    };
    return dfs(dfs, root);
  }

private:
  void update(np c) {
    c->prod = c->x;
    if (c->l) c->prod = MX::op(c->l->prod, c->prod);
    if (c->r) c->prod = MX::op(c->prod, c->r->prod);
  }

  np copy_node(np c) {
    if (!c || !PERSISTENT) return c;
    assert(pid < NODES);
    pool[pid].idx = c->idx;
    pool[pid].l = c->l;
    pool[pid].r = c->r;
    pool[pid].x = c->x;
    pool[pid].prod = c->prod;
    return &(pool[pid++]);
  }

  np set_rec(np c, ll l, ll r, ll i, X x) {
    if (!c) {
      c = new_node(i, x);
      return c;
    }
    c = copy_node(c);
    if (c->idx == i) {
      c->x = x;
      update(c);
      return c;
    }
    ll m = (l + r) / 2;
    if (i < m) {
      if (c->idx < i) swap(c->idx, i), swap(c->x, x);
      c->l = set_rec(c->l, l, m, i, x);
    }
    if (m <= i) {
      if (i < c->idx) swap(c->idx, i), swap(c->x, x);
      c->r = set_rec(c->r, m, r, i, x);
    }
    update(c);
    return c;
  }

  void prod_rec(np c, ll l, ll r, ll ql, ll qr, X &x) {
    chmax(ql, l);
    chmin(qr, r);
    if (ql >= qr || !c) return;
    if (l == ql && r == qr) {
      x = MX::op(x, c->prod);
      return;
    }
    ll m = (l + r) / 2;
    prod_rec(c->l, l, m, ql, qr, x);
    if (ql <= (c->idx) && (c->idx) < qr) x = MX::op(x, c->x);
    prod_rec(c->r, m, r, ql, qr, x);
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

using mint = modint998;
using Mono = Monoid_Affine<mint>;

int get() {
  int x;
  scanf("%d", &x);
  return x;
}

void solve() {
  ll N = get(), Q = get();
  Dynamic_SegTree_Sparse<Mono, false> seg(Q, 0, N);
  using np = decltype(seg)::np;
  np root = seg.new_root();

  FOR(Q) {
    ll t = get();
    if (t == 0) {
      ll i = get(), a = get(), b = get();
      root = seg.set(root, i, {mint(a), mint(b)});
    }
    if (t == 1) {
      ll L = get(), R = get(), x = get();
      mint ANS = Mono::eval(seg.prod(root, L, R), mint(x));
      printf("%d\n", ANS.val);
    }
  }
}

signed main() { solve(); }
