#include <vector>
#include <cstdio>
#include <algorithm>
#include <cassert>
#include <numeric>

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

#define MIN(v) *min_element(all(v))
#define MAX(v) *max_element(all(v))
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

pair<int, int> closest_pair_dc(vc<Point<ll>> point) {
  int N = len(point);
  assert(N >= 2);

  auto I = argsort(point);
  point = rearrange(point, I);

  ll best = -1;
  pair<int, int> best_pair = {-1, -1};

  auto upd = [&](int i, int j) -> void {
    Point<ll> p = point[i] - point[j];
    ll d = p.dot(p);
    if (best == -1 || best > d) { best = d, best_pair = {I[i], I[j]}; }
  };
  upd(0, 1);

  auto dfs = [&](auto &dfs, int L, int R) -> vc<int> {
    // return: [L,R) を y について sort したもの
    if (R == L + 1) return {L};
    int M = (L + R) / 2;
    vc<int> I0 = dfs(dfs, L, M);
    vc<int> I1 = dfs(dfs, M, R);
    vc<int> I;
    vc<int> near;
    int a = 0, b = 0;
    FOR(R - L) {
      int idx = [&]() -> int {
        if (a == len(I0)) return I1[b++];
        if (b == len(I1)) return I0[a++];
        int i = I0[a], j = I1[b];
        if (point[i].y < point[j].y) {
          ++a;
          return i;
        }
        ++b;
        return j;
      }();
      I.eb(idx);
      ll dx = point[M].x - point[idx].x;
      if (dx * dx > best) { continue; }
      FOR_R(k, len(near)) {
        int j = near[k];
        ll dy = point[idx].y - point[j].y;
        if (best == 0 || dy * dy > best) break;
        upd(idx, j);
      }
      near.eb(idx);
    }
    return I;
  };
  dfs(dfs, 0, N);
  return best_pair;
}

using P = Point<ll>;

void solve() {
  int N;
  scanf("%d", &N);
  vc<P> point(N);
  FOR(i, N) { scanf("%lld %lld", &point[i].x, &point[i].y); }
  auto [a, b] = closest_pair_dc(point);
  printf("%d %d\n", a, b);
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
  return 0;
}
