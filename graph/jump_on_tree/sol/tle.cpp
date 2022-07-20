#include <vector>
#include <cassert>
#include <algorithm>
#include <cstdio>
#include <deque>

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

#define eb emplace_back

void solve() {
  int N, Q;
  scanf("%d %d", &N, &Q);
  // solve O(NQ) by bfs

  vector<vector<int>> G(N);
  FOR(N - 1) {
    int a, b;
    scanf("%d %d", &a, &b);
    G[a].eb(b);
    G[b].eb(a);
  }

  auto jump = [&](int s, int t, int k) -> int {
    // bfs from s
    vc<int> dist(N, -1), par(N, -1);
    deque<int> que = {s};
    que.eb(s);
    dist[s] = 0;
    while (dist[t] == -1) {
      auto v = que.front();
      que.pop_front();
      for (auto &&to: G[v]) {
        if (dist[to] != -1) continue;
        dist[to] = dist[v] + 1;
        par[to] = v;
        que.eb(to);
      }
    }
    vc<int> P = {t};
    while (P.back() != s) { P.eb(par[P.back()]); }
    reverse(P.begin(), P.end());

    if (k >= int(P.size())) return -1;
    return P[k];
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
