#include <iostream>
#include <set>
#include <vector>
using namespace std;
using i64 = long long;

constexpr int MOD = 998244353;
int N, Q;
std::vector<i64> A, B;
std::vector<std::set<i64>> G;

i64 dfs(i64 u, i64 f, i64 v, i64 ans) {
  ans = (A[u] * ans + B[u]) % MOD;
  if(u == v) return ans;
  for(i64 t: G[u]) {
    if(f == t) continue;
    i64 tmp = dfs(t, u, v, ans);
    if(tmp != -1) {
      return tmp;
    }
  }
  return -1;
}

int main() {
  scanf("%d%d", &N, &Q);
  A.resize(N);
  B.resize(N);
  G.resize(N);
  for(int i = 0;i < N;i++) {
    scanf("%lld%lld", &A[i], &B[i]);
  }
  for(int i = 0;i < N - 1;i++) {
    i64 u, v;
    scanf("%lld%lld", &u, &v);
    G[u].insert(v);
    G[v].insert(u);
  }

  for(int i = 0; i < Q;i++) {
    i64 q, a, b, c;
    scanf("%lld%lld%lld%lld", &q, &a, &b, &c);
    if(q == 0) {
      i64 d;
      scanf("%lld", &d);
      G[a].erase(b);
      G[b].erase(a);
      G[c].insert(d);
      G[d].insert(c);
    }
    else if(q == 1) {
      A[a] = b;
      B[a] = c;
    }
    else {
      cout << dfs(a, -1, b, c) << endl;
    }
  }
}
