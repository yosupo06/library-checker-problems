#include <vector>
#include <cstdio>
#include <cassert>
#include <algorithm>
#include <numeric>
#include <string>
#include <tuple>

using namespace std;

using ll = long long;

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

#define all(x) x.begin(), x.end()
#define len(x) ll(x.size())
#define elif else if

#define eb emplace_back
#define mp make_pair
#define fi first
#define se second

#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

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

// A[I[0]], A[I[1]], ...
template <typename T>
vc<T> rearrange(const vc<T> &A, const vc<int> &I) {
  vc<T> B(len(I));
  FOR(i, len(I)) B[i] = A[I[i]];
  return B;
}
template <typename T>
struct Point {
  T x, y;

  Point() : x(0), y(0) {}

  template <typename A, typename B>
  Point(A x, B y) : x(x), y(y) {}

  template <typename A, typename B>
  Point(pair<A, B> p) : x(p.fi), y(p.se) {}

  Point operator+(Point p) const { return {x + p.x, y + p.y}; }
  Point operator-(Point p) const { return {x - p.x, y - p.y}; }
  bool operator==(Point p) const { return x == p.x && y == p.y; }
  bool operator!=(Point p) const { return x != p.x || y != p.y; }
  Point operator-() const { return {-x, -y}; }
  Point operator*(T t) const { return {x * t, y * t}; }
  Point operator/(T t) const { return {x / t, y / t}; }

  bool operator<(Point p) const {
    if (x != p.x) return x < p.x;
    return y < p.y;
  }
  T dot(Point other) { return x * other.x + y * other.y; }
  T det(Point other) { return x * other.y - y * other.x; }
};

template <typename T>
vector<int> ConvexHull(vector<Point<T>> &XY, string mode = "full",
                       bool inclusive = false) {
  assert(mode == "full" || mode == "lower" || mode == "upper");
  ll N = XY.size();
  if (N == 1) return {0};
  if (N == 2) {
    if (XY[0] < XY[1]) return {0, 1};
    if (XY[1] < XY[0]) return {1, 0};
    if (inclusive) return {0, 1};
    return {0};
  }
  vc<int> I = argsort(XY);

  auto check = [&](ll i, ll j, ll k) -> bool {
    auto xi = XY[i].x, yi = XY[i].y;
    auto xj = XY[j].x, yj = XY[j].y;
    auto xk = XY[k].x, yk = XY[k].y;
    auto dx1 = xj - xi, dy1 = yj - yi;
    auto dx2 = xk - xj, dy2 = yk - yj;
    T det = dx1 * dy2 - dy1 * dx2;
    return (inclusive ? det >= 0 : det > 0);
  };

  auto calc = [&]() {
    vector<int> P;
    for (auto &&k: I) {
      while (P.size() > 1) {
        auto i = P[P.size() - 2];
        auto j = P[P.size() - 1];
        if (check(i, j, k)) break;
        P.pop_back();
      }
      P.eb(k);
    }
    return P;
  };

  vc<int> P;
  if (mode == "full" || mode == "lower") {
    vc<int> Q = calc();
    P.insert(P.end(), all(Q));
  }
  if (mode == "full" || mode == "upper") {
    if (!P.empty()) P.pop_back();
    reverse(all(I));
    vc<int> Q = calc();
    P.insert(P.end(), all(Q));
  }
  if (mode == "upper") reverse(all(P));
  while (len(P) >= 2 && XY[P[0]] == XY[P.back()]) P.pop_back();
  return P;
}

using P = Point<ll>;

pair<int, int> furthest_pair(vc<P> point) {
  ll best = -1;
  pair<int, int> ANS = {-1, -1};

  auto dist = [&](int i, int j) -> ll {
    P p = point[i] - point[j];
    return p.dot(p);
  };
  auto upd = [&](int i, int j) -> void {
    if (chmax(best, dist(i, j))) ANS = {i, j};
  };
  upd(0, 1);

  auto I = ConvexHull(point);
  int n = len(I);
  if (n == 1) return ANS;
  if (n == 2) { return {I[0], I[1]}; }
  FOR(i, n + 1) I.eb(I[i]);

  int j = 1;
  FOR(i, n) {
    chmax(j, i);
    while (j < 2 * n && dist(I[i], I[j]) < dist(I[i], I[j + 1])) ++j;
    upd(I[i], I[j]);
  }
  return ANS;
}

void solve() {
  int N;
  scanf("%d", &N);
  vc<P> point(N);
  FOR(i, N) { scanf("%lld %lld", &point[i].x, &point[i].y); }
  auto [a, b] = furthest_pair(point);
  printf("%d %d\n", a, b);
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
  return 0;
}
