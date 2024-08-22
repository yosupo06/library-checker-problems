#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>

using namespace std;

using ll = long long;
using pi = pair<ll, ll>;
using vi = vector<ll>;
using u32 = unsigned int;
using u64 = unsigned long long;
using i128 = __int128;

template <class T>
using vc = vector<T>;

// https://trap.jp/post/1224/
#define FOR1(a) for (ll _ = 0; _ < ll(a); ++_)
#define FOR2(i, a) for (ll i = 0; i < ll(a); ++i)
#define FOR3(i, a, b) for (ll i = a; i < ll(b); ++i)
#define FOR4(i, a, b, c) for (ll i = a; i < ll(b); i += (c))
#define FOR1_R(a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR2_R(i, a) for (ll i = (a)-1; i >= ll(0); --i)
#define FOR3_R(i, a, b) for (ll i = (b)-1; i >= ll(a); --i)
#define FOR4_R(i, a, b, c) for (ll i = (b)-1; i >= ll(a); i -= (c))
#define overload4(a, b, c, d, e, ...) e
#define FOR(...) overload4(__VA_ARGS__, FOR4, FOR3, FOR2, FOR1)(__VA_ARGS__)
#define FOR_R(...) \
  overload4(__VA_ARGS__, FOR4_R, FOR3_R, FOR2_R, FOR1_R)(__VA_ARGS__)

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

void solve() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  // solve by doubling.
  vector<vector<int>> G(N);
  FOR(N - 1) {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].eb(b);
    G[b].eb(a);
  }
  vc<int> par(N, -1), dep(N);

  auto dfs = [&](auto &dfs, int v) -> void {
    for (auto &&to: G[v]) {
      if (to == par[v]) continue;
      par[to] = v;
      dep[to] = dep[v] + 1;
      dfs(dfs, to);
    }
  };
  dfs(dfs, 0);

  const int K = 20;
  vector<vector<int>> dat(K, vector<int>(N, -1));
  dat[0] = par;
  FOR(k, K - 1) {
    FOR(v, N) {
      int p = dat[k][v];
      if (p == -1) continue;
      dat[k + 1][v] = dat[k][p];
    }
  }

  auto LA = [&](int v, int x) -> int {
    assert(x <= dep[v]);
    FOR(k, K) {
      if (x & 1 << k) { v = dat[k][v]; }
    }
    return v;
  };

  auto LCA = [&](int a, int b) -> int {
    if (dep[a] > dep[b]) swap(a, b);
    b = LA(b, dep[b] - dep[a]);
    assert(dep[a] == dep[b]);
    if (a == b) return a;
    FOR_R(k, K) {
      int pa = dat[k][a];
      int pb = dat[k][b];
      if (pa == pb) continue;
      a = pa;
      b = pb;
    }
    assert(a != b);
    assert(par[a] == par[b]);
    return par[a];
  };

  auto jump = [&](int s, int t, int k) -> int {
    int lca = LCA(s, t);
    int x1 = dep[s] - dep[lca];
    int x2 = dep[t] - dep[lca];
    if (x1 + x2 < k) return -1;
    if (k <= x1) return LA(s, k);
    return LA(t, x1 + x2 - k);
  };

  FOR(Q) {
    int s, t, k;
    scanf("%d %d %d", &s, &t, &k);
    printf("%d\n", jump(s, t, k));
  }
}

signed main() {
  ll T = 1;
  // LL(T);
  FOR(T) solve();

  return 0;
}
