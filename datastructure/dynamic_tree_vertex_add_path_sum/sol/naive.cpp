#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;

int N, Q;
std::vector<i64> A;
std::vector<std::set<i64>> G;

i64 dfs(i64 u, i64 f, i64 v, i64 ans) {
  if(u == v) return ans + A[u];
  for(i64 t: G[u]) {
    if(f == t) continue;
    i64 tmp = dfs(t, u, v, ans + A[u]);
    if(tmp != -1) {
      return tmp;
    }
  }
  return -1;
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
      i64 c;
      scanf("%lld", &c);
      G[a].erase(b);
      G[b].erase(a);
      G[b].insert(c);
      G[c].insert(b);
    }
    else if(q == 1) {
      A[a] += b;
    }
    else {
      cout << dfs(a, -1, b, 0) << endl;
    }
  }
}
