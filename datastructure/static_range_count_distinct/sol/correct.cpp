#include <cstdio>
#include <vector>
#include <cassert>
#include <map>

using namespace std;

using ll = long long;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vc<T>>;

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

template <class Monoid>
struct SegTree {
  using MX = Monoid;
  using X = typename MX::value_type;
  using value_type = X;
  vc<X> dat;
  int n, log, size;

  SegTree() {}
  SegTree(int n) { build(n); }

  void build(int m) {
    n = m, log = 1;
    while ((1 << log) < n) ++log;
    size = 1 << log;
    dat.assign(size << 1, MX::unit());
  }

  void update(int i) { dat[i] = Monoid::op(dat[2 * i], dat[2 * i + 1]); }
  void set(int i, const X &x) {
    assert(i < n);
    dat[i += size] = x;
    while (i >>= 1) update(i);
  }

  X prod(int L, int R) {
    assert(0 <= L && L <= R && R <= n);
    X vl = Monoid::unit(), vr = Monoid::unit();
    L += size, R += size;
    while (L < R) {
      if (L & 1) vl = Monoid::op(vl, dat[L++]);
      if (R & 1) vr = Monoid::op(dat[--R], vr);
      L >>= 1, R >>= 1;
    }
    return Monoid::op(vl, vr);
  }
};

template <typename X>
struct Monoid_Add {
  using value_type = X;
  static constexpr X op(const X &x, const X &y) noexcept { return x + y; }
  static constexpr X inverse(const X &x) noexcept { return -x; }
  static constexpr X power(const X &x, ll n) noexcept { return X(n) * x; }
  static constexpr X unit() { return X(0); }
  static constexpr bool commute = true;
};

int main() {
  int N, Q;
  scanf("%d%d", &N, &Q);

  vector<int> A(N);
  FOR(i, N) scanf("%d", &A[i]);

  vc<int> ANS(Q);

  // r -> q, l
  vvc<pair<int, int>> query(N);
  FOR(q, Q) {
    int l, r;
    scanf("%d%d", &l, &r);
    if (l == r) continue;
    query[r - 1].eb(q, l);
  }

  SegTree<Monoid_Add<int>> seg(N);
  map<int, int> MP;
  FOR(r, N) {
    int x = A[r];
    int p = MP.count(x) ? MP[x] : -1;
    if (p != -1) seg.set(p, 0);
    seg.set(r, 1);
    MP[x] = r;
    for (auto x: query[r]) {
      int q = x.first, l = x.second;
      ANS[q] = seg.prod(l, r + 1);
    }
  }

  for (int q = 0; q < Q; ++q) printf("%d\n", ANS[q]);

  return 0;
}
