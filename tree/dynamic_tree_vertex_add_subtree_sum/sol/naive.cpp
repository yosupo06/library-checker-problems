#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;

int N, Q;
std::vector<i64> A;
std::vector<std::set<i64>> G;

i64 dfs(i64 v, i64 f) {
  i64 ans = A[v];
  for(i64 t: G[v]) {
    if(f == t) continue;
    ans += dfs(t, v);
  }
  return ans;
}

int main() {
  scanf("%d%d", &N, &Q);
  A.resize(N);
  G.resize(N);
  for(int i = 0;i < N;i++) {
    scanf("%lld", &A[i]);
  }
  for(int i = 0;i < N - 1;i++) {
    i64 u, v;
    scanf("%lld%lld", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
  }

  for(int i = 0; i < Q;i++) {
    i64 q, a, b;
    scanf("%lld%lld%lld", &q, &a, &b);
    if(q == 0) {
      i64 c, d;
      scanf("%lld%lld", &c, &d);
      G[a].erase(b);
      G[b].erase(a);
      G[c].insert(d);
      G[d].insert(c);
    }
    else if(q == 1) {
      A[a] += b;
    }
    else {
      cout << dfs(a, b) << endl;
    }
  }
}
