#include <cstdio>
#include <vector>
#include "acl.h"

using namespace std;
using namespace atcoder;

using mint = modint998244353;

mint id() { return 0; }
mint op(const mint &a, const mint &b) { return a + b; }
mint inv(const mint &a) { return -a; }

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<vector<pair<int, mint>>> g(N);
  vector<mint> a(N, id());
  vector<int> vis(N);
  iota(vis.begin(), vis.end(), 0);

  //op(a[v1], d) = a[v2]
  auto try_add = [&](int v1, int v2, mint d) {
    g[v1].emplace_back(v2, d);
    g[v2].emplace_back(v1, inv(d));

    bool valid = true;
    vector ap(N, id());
    vector visp(N, -1);
    int s = 0;
    auto dfs = [&](int v, auto &&self) -> void {
      visp[v] = s;
      for(auto [u, x] : g[v]) {
        if (visp[u] != -1) {
          valid = valid and op(ap[v], x) == ap[u];
        } else {
          ap[u] = op(ap[v], x);
          self(u, self);
        }
      }
    };
    for(int v = 0; v < N; v++) if (visp[v] == -1) {
      dfs(v, dfs);
      s++;
    }

    if (valid) {
      a.swap(ap);
      vis.swap(visp);
    } else {
      g[v1].pop_back();
      g[v2].pop_back();
    }

    return valid;
  };

  while(Q--) {
    int t, u, v;
    scanf("%d %d %d", &t, &u, &v);
    if (t == 0) {
      int x;
      scanf("%d", &x);
      printf("%d\n", try_add(v, u, mint(x)));
    } else {
      if (vis[u] != vis[v])
        printf("%d\n", -1);
      else
        printf("%d\n", op(inv(a[v]), a[u]).val());
    }
  }

  return 0;
}
