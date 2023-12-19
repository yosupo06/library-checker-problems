#include <bits/stdc++.h>

using namespace std;

using ll = long long;

template <class T>
using vc = vector<T>;
template <class T>
using vvc = vector<vector<T>>;

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
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

template <typename F>
ll binary_search(F check, ll ok, ll ng, bool check_ok = true) {
  if (check_ok) assert(check(ok));
  while (abs(ok - ng) > 1) {
    auto x = (ng + ok) / 2;
    (check(x) ? ok : ng) = x;
  }
  return ok;
}

template <class T, class S>
inline bool chmax(T &a, const S &b) {
  return (a < b ? a = b, 1 : 0);
}
template <class T, class S>
inline bool chmin(T &a, const S &b) {
  return (a > b ? a = b, 1 : 0);
}

// stable sort
template <typename T>
vector<int> argsort(const vector<T> &A) {
  vector<int> ids(len(A));
  iota(all(ids), 0);
  sort(all(ids),
       [&](int i, int j) { return (A[i] == A[j] ? i < j : A[i] < A[j]); });
  return ids;
}

template <typename X>
struct Monoid_Add {
  using value_type = X;
  static constexpr X op(const X &x, const X &y) noexcept { return x + y; }
  static constexpr X inverse(const X &x) noexcept { return -x; }
  static constexpr X power(const X &x, ll n) noexcept { return X(n) * x; }
  static constexpr X unit() { return X(0); }
  static constexpr bool commute = true;
};

template <typename Monoid, typename XY, bool SMALL_X = false>
struct FenwickTree_2D {
  using G = Monoid;
  using E = typename G::value_type;
  static_assert(G::commute);
  int N;
  vc<XY> keyX;
  XY min_X;
  vc<int> indptr;
  vc<XY> keyY;
  vc<E> dat;

  FenwickTree_2D(vc<XY> &X, vc<XY> &Y, vc<E> wt) { build(X, Y, wt); }
  FenwickTree_2D(vc<XY> &X, vc<XY> &Y) {
    vc<E> wt(len(X), G::unit());
    build(X, Y, wt);
  }

  inline int xtoi(XY x) {
    return (SMALL_X ? clamp<int>(x - min_X, 0, N) : LB(keyX, x));
  }
  inline int nxt(int i) { return i + ((i + 1) & -(i + 1)); }
  inline int prev(int i) { return i - ((i + 1) & -(i + 1)); }

  void build(vc<XY> &X, vc<XY> &Y, vc<E> wt) {
    assert(len(X) == len(Y) && len(X) == len(wt));
    if (!SMALL_X) {
      keyX = X;
      UNIQUE(keyX);
      N = len(keyX);
    } else {
      min_X = (len(X) == 0 ? 0 : MIN(X));
      N = (len(X) == 0 ? 0 : MAX(X)) - min_X + 1;
      keyX.resize(N);
      FOR(i, N) keyX[i] = min_X + i;
    }
    vvc<XY> keyY_raw(N);
    vvc<E> dat_raw(N);
    for (auto &&i: argsort(Y)) {
      int ix = xtoi(X[i]);
      XY y = Y[i];
      while (ix < N) {
        auto &KY = keyY_raw[ix];
        if (len(KY) == 0 || KY.back() < y) {
          KY.eb(y);
          dat_raw[ix].eb(wt[i]);
        } else {
          dat_raw[ix].back() = G::op(dat_raw[ix].back(), wt[i]);
        }
        ix = nxt(ix);
      }
    }

    indptr.assign(N + 1, 0);
    FOR(i, N) indptr[i + 1] = indptr[i] + len(keyY_raw[i]);
    keyY.resize(indptr.back());
    dat.resize(indptr.back());
    FOR(i, N) FOR(j, indptr[i + 1] - indptr[i]) {
      keyY[indptr[i] + j] = keyY_raw[i][j];
      dat[indptr[i] + j] = dat_raw[i][j];
    }
    FOR(i, N) {
      int n = indptr[i + 1] - indptr[i];
      FOR(j, n - 1) {
        int k = nxt(j);
        if (k < n)
          dat[indptr[i] + k] = G::op(dat[indptr[i] + k], dat[indptr[i] + j]);
      }
    }
  }

  void add(XY x, XY y, E val) { multiply(x, y, val); }
  void multiply(XY x, XY y, E val) {
    int i = xtoi(x);
    assert(keyX[i] == x);
    while (i < N) { multiply_i(i, y, val), i = nxt(i); }
  }

  E sum(XY lx, XY rx, XY ly, XY ry) { return prod(lx, rx, ly, ry); }
  E prod(XY lx, XY rx, XY ly, XY ry) {
    E pos = G::unit(), neg = G::unit();
    int L = xtoi(lx) - 1, R = xtoi(rx) - 1;
    while (L < R) { pos = G::op(pos, prod_i(R, ly, ry)), R = prev(R); }
    while (R < L) { neg = G::op(neg, prod_i(L, ly, ry)), L = prev(L); }
    return G::op(pos, G::inverse(neg));
  }

  E prefix_sum(XY rx, XY ry) { return prefix_prod(rx, ry); }
  E prefix_prod(XY rx, XY ry) {
    E pos = G::unit();
    int R = xtoi(rx) - 1;
    while (R >= 0) { pos = G::op(pos, prefix_prod_i(R, ry)), R = prev(R); }
    return pos;
  }

private:
  void multiply_i(int i, XY y, E val) {
    int LID = indptr[i], n = indptr[i + 1] - indptr[i];
    auto it = keyY.begin() + LID;
    int j = lower_bound(it, it + n, y) - it;
    while (j < n) { dat[LID + j] = G::op(dat[LID + j], val), j = nxt(j); }
  }

  E prod_i(int i, XY ly, XY ry) {
    E pos = G::unit(), neg = G::unit();
    int LID = indptr[i], n = indptr[i + 1] - indptr[i];
    auto it = keyY.begin() + LID;
    int L = lower_bound(it, it + n, ly) - it - 1;
    int R = lower_bound(it, it + n, ry) - it - 1;
    while (L < R) { pos = G::op(pos, dat[LID + R]), R = prev(R); }
    while (R < L) { neg = G::op(neg, dat[LID + L]), L = prev(L); }
    return G::op(pos, G::inverse(neg));
  }

  E prefix_prod_i(int i, XY ry) {
    E pos = G::unit();
    int LID = indptr[i], n = indptr[i + 1] - indptr[i];
    auto it = keyY.begin() + LID;
    int R = lower_bound(it, it + n, ry) - it - 1;
    while (R >= 0) { pos = G::op(pos, dat[LID + R]), R = prev(R); }
    return pos;
  }
};

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  using QT = tuple<int, int, int, int, int>;
  vc<QT> QUERY;
  FOR(N) {
    int x1, y1, x2, y2, w;
    scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
    QUERY.eb(x1, x2, y1, y2, w);
  }

  FOR(Q) {
    int t;
    scanf("%d", &t);
    if (t == 0) {
      int x1, y1, x2, y2, w;
      scanf("%d %d %d %d %d", &x1, &y1, &x2, &y2, &w);
      QUERY.eb(x1, x2, y1, y2, w);
    } else {
      int x, y;
      scanf("%d %d", &x, &y);
      QUERY.eb(-1, x, y, 0, 0);
    }
  }

  vc<int> X, Y;
  for (auto &[x1, x2, y1, y2, w]: QUERY) {
    if (x1 == -1) continue;
    X.eb(x1), Y.eb(y1);
    X.eb(x1), Y.eb(y2);
    X.eb(x2), Y.eb(y1);
    X.eb(x2), Y.eb(y2);
  }

  FenwickTree_2D<Monoid_Add<ll>, int> bit(X, Y);

  for (auto &[x1, x2, y1, y2, w]: QUERY) {
    if (x1 == -1) {
      int x = x2, y = y1;
      ll ans = bit.sum(0, x + 1, 0, y + 1);
      printf("%lld\n", ans);
    } else {
      bit.add(x1, y1, +w);
      bit.add(x1, y2, -w);
      bit.add(x2, y1, -w);
      bit.add(x2, y2, +w);
    }
  }

  return 0;
}
