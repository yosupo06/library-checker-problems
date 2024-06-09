#include <vector>
#include <cstdio>

using namespace std;

using ll = long long;

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

#define FOR_subset(t, s) \
  for (ll t = (s); t >= 0; t = (t == 0 ? -1 : (t - 1) & (s)))
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

void solve() {
  int N;
  scanf("%d", &N);
  ll best = -1;
  vi X(N), Y(N);
  FOR(i, N) scanf("%lld %lld", &X[i], &Y[i]);

  pair<int, int> ANS = {-1, -1};
  FOR(j, N) FOR(i, j) {
    ll dx = X[i] - X[j], dy = Y[i] - Y[j];
    ll d = dx * dx + dy * dy;
    if (best == -1 || best > d) best = d, ANS = {i, j};
  }
  auto [a, b] = ANS;
  printf("%d %d\n", a, b);
}

signed main() {
  int T;
  scanf("%d", &T);
  FOR(T) solve();
  return 0;
}
