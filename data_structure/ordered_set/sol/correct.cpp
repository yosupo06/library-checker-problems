#include <vector>
#include <cstdio>
#include <cassert>
#include <tuple>
#include <cstdlib>

using namespace std;

using ll = long long;

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
#define fi first
#define se second

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

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

  Dynamic_SegTree_Sparse(int NODES, ll L0, ll R0) : NODES(NODES), L0(L0), R0(R0), pid(0) { pool = new Node[NODES]; }
  ~Dynamic_SegTree_Sparse() { delete[] pool; }

  np new_root() { return nullptr; }

  np new_node(ll idx, const X x) {
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

  template <typename F>
  ll max_right(np root, F check, ll L) {
    assert(L0 <= L && L <= R0 && check(MX::unit()));
    X x = MX::unit();
    return max_right_rec(root, check, L0, R0, L, x);
  }

  template <typename F>
  ll min_left(np root, F check, ll R) {
    assert(L0 <= R && R <= R0 && check(MX::unit()));
    X x = MX::unit();
    return min_left_rec(root, check, L0, R0, R, x);
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

  template <typename F>
  ll max_right_rec(np c, const F &check, ll l, ll r, ll ql, X &x) {
    if (!c || r <= ql) return R0;
    if (check(MX::op(x, c->prod))) {
      x = MX::op(x, c->prod);
      return R0;
    }
    ll m = (l + r) / 2;
    ll k = max_right_rec(c->l, check, l, m, ql, x);
    if (k != R0) return k;
    if (ql <= (c->idx)) {
      x = MX::op(x, c->x);
      if (!check(x)) return c->idx;
    }
    return max_right_rec(c->r, check, m, r, ql, x);
  }

  template <typename F>
  ll min_left_rec(np c, const F &check, ll l, ll r, ll qr, X &x) {
    if (!c || qr <= l) return L0;
    if (check(MX::op(c->prod, x))) {
      x = MX::op(c->prod, x);
      return L0;
    }
    ll m = (l + r) / 2;
    ll k = min_left_rec(c->r, check, m, r, qr, x);
    if (k != L0) return k;
    if (c->idx < qr) {
      x = MX::op(c->x, x);
      if (!check(x)) return c->idx + 1;
    }
    return min_left_rec(c->l, check, l, m, qr, x);
  }
};

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

void solve() {
  int N, Q;
  scanf("%d%d", &N, &Q);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) scanf("%d", &A[i]);

  const int INF = 1'000'000'100;

  Dynamic_SegTree_Sparse<Monoid_Add<int>, 0> seg(N + Q, 0, INF);
  using np = decltype(seg)::np;
  np root = seg.new_root();

  for (auto &x: A) root = seg.set(root, x, 1);

  for (int q = 0; q < Q; ++q) {
    int t, x;
    scanf("%d%d", &t, &x);
    if (t == 0) { root = seg.set(root, x, 1); }
    if (t == 1) { root = seg.set(root, x, 0); }
    if (t == 2) {
      int ans = seg.max_right(
          root, [&](int sm) -> bool { return sm < x; }, 0);
      if (ans == INF) ans = -1;
      printf("%d\n", ans);
    }
    if (t == 3) {
      int ans = seg.prod(root, 0, x + 1);
      printf("%d\n", ans);
    }
    if (t == 4) {
      int ans = seg.min_left(
          root, [&](int sm) -> bool { return sm == 0; }, x + 1);
      --ans;
      printf("%d\n", ans);
    }

    if (t == 5) {
      int ans = seg.max_right(
          root, [&](int sm) -> bool { return sm == 0; }, x);
      if (ans == INF) ans = -1;
      printf("%d\n", ans);
    }
  }
}

signed main() { solve(); }
