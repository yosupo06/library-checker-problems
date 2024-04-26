#include <vector>
#include <cassert>
#include <algorithm>
#include <string>
#include <array>
#include <numeric>

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
#define mp make_pair
#define mt make_tuple
#define fi first
#define se second

#define LB(c, x) distance((c).begin(), lower_bound(all(c), (x)))
#define UB(c, x) distance((c).begin(), upper_bound(all(c), (x)))
#define UNIQUE(x) \
  sort(all(x)), x.erase(unique(all(x)), x.end()), x.shrink_to_fit()

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
vector<int> ConvexHull(vector<pair<T, T>> &XY, string mode = "full",
                       bool inclusive = false) {
  assert(mode == "full" || mode == "lower" || mode == "upper");
  ll N = XY.size();
  if (N == 0) return {};
  if (N == 1) return {0};
  if (N == 2) {
    if (XY[0] < XY[1]) return {0, 1};
    if (XY[1] < XY[0]) return {1, 0};
    if (inclusive) return {0, 1};
    return {0};
  }
  vc<int> I = argsort(XY);

  auto check = [&](ll i, ll j, ll k) -> bool {
    auto xi = XY[i].fi, yi = XY[i].se;
    auto xj = XY[j].fi, yj = XY[j].se;
    auto xk = XY[k].fi, yk = XY[k].se;
    auto dx1 = xj - xi, dy1 = yj - yi;
    auto dx2 = xk - xj, dy2 = yk - yj;
    T det = dx1 * dy2 - dy1 * dx2;
    return (inclusive ? det >= 0 : det > 0);
  };

  auto calc = [&]() {
    vector<int> P;
    for (auto &&k: I) {
      if (len(P) && XY[P.back()] == XY[k]) continue;
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
  if (len(P) >= 2 && XY[P[0]] == XY[P.back()]) P.pop_back();
  return P;
}

void solve() {
  int N;
  scanf("%d", &N);
  using P = pair<ll, ll>;
  vc<P> point(N);
  FOR(i, N) {
    int x, y;
    scanf("%d %d", &x, &y);
    point[i] = {x, y};
  }

  auto I = ConvexHull<ll>(point, "full");

  int k = (N == 0 ? 0 : I.size() / 2);
  rotate(I.begin(), I.begin() + k, I.end());

  int M = len(I);
  printf("%d\n", M);
  for (auto &i: I) {
    P p = point[i];
    int x = p.fi, y = p.se;
    printf("%d %d\n", x, y);
  }
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
}
