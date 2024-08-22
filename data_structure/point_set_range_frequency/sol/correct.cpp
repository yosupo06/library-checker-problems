#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <map>

using namespace std;

using ll = long long;
using u32 = unsigned int;
using u64 = unsigned long long;

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

// 常にほとんどの要素が unit であることが保証されるような動的セグ木
// したがって、default_prod の類は持たせられず、acted monoid も一般には扱えない
// 永続化しない場合のノード数を O(N) に抑えることができるのが利点
template <typename Monoid, bool PERSISTENT, int NODES>
struct Dynamic_SegTree_Sparse {
  using MX = Monoid;
  using X = typename MX::value_type;

  struct Node {
    ll idx;
    Node *l, *r;
    X prod, x;
  };

  const ll L0, R0;
  Node *pool;
  int pid;
  using np = Node *;
  vc<np> FREE;

  Dynamic_SegTree_Sparse(ll L0, ll R0) : L0(L0), R0(R0), pid(0) {
    pool = new Node[NODES];
  }

  // 木 dp のマージのときなどに使用すると MLE 回避できることがある
  // https://codeforces.com/problemset/problem/671/D
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

  X prod_all(np root) { return prod(root, L0, R0); }

  np set(np root, ll i, const X &x) {
    assert(L0 <= i && i < R0);
    return set_rec(root, L0, R0, i, x);
  }

  np multiply(np root, ll i, const X &x) {
    assert(L0 <= i && i < R0);
    return multiply_rec(root, L0, R0, i, x);
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

  void reset() {
    pid = 0;
    FREE.clear();
  }

  vc<pair<ll, X>> get_all(np root) {
    vc<pair<ll, X>> res;
    auto dfs = [&](auto &dfs, np c) -> void {
      if (!c) return;
      dfs(dfs, c->l);
      res.eb(c->idx, c->x);
      dfs(dfs, c->r);
    };
    dfs(dfs, root);
    return res;
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

  np multiply_rec(np c, ll l, ll r, ll i, X x) {
    if (!c) {
      c = new_node(i, x);
      return c;
    }
    c = copy_node(c);
    if (c->idx == i) {
      c->x = MX::op(c->x, x);
      update(c);
      return c;
    }
    ll m = (l + r) / 2;
    if (i < m) {
      if (c->idx < i) swap(c->idx, i), swap(c->x, x);
      c->l = multiply_rec(c->l, l, m, i, x);
    }
    if (m <= i) {
      if (i < c->idx) swap(c->idx, i), swap(c->x, x);
      c->r = multiply_rec(c->r, m, r, i, x);
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

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  vector<int> A(N);
  for (int i = 0; i < N; ++i) scanf("%d", &A[i]);

  Dynamic_SegTree_Sparse<Monoid_Add<int>, 0, 1 << 20> seg(0, N);
  using np = decltype(seg)::np;
  map<int, np> root;

  auto add = [&](int i) -> void {
    int x = A[i];
    if (!root.count(x)) root[x] = seg.new_root();
    root[x] = seg.multiply(root[x], i, +1);
  };

  auto rm = [&](int i) -> void {
    int x = A[i];
    if (!root.count(x)) root[x] = seg.new_root();
    root[x] = seg.multiply(root[x], i, -1);
  };

  auto query = [&](int L, int R, int x) -> int {
    if (!root.count(x)) return 0;
    return seg.prod(root[x], L, R);
  };

  for (int i = 0; i < N; ++i) add(i);

  for (int q = 0; q < Q; ++q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int i, x;
      scanf("%d %d", &i, &x);
      rm(i), A[i] = x, add(i);
    }
    if (t == 1) {
      int l, r, x;
      scanf("%d %d %d", &l, &r, &x);
      int ans = query(l, r, x);
      printf("%d\n", ans);
    }
  }
  return 0;
}
