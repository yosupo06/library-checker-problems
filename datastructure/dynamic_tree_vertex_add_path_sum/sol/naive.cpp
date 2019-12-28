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
  cin >> N >> Q;
  A.resize(N);
  G.resize(N);
  for(int i = 0;i < N;i++) {
    cin >> A[i];
  }
  for(int i = 0;i < N - 1;i++) {
    i64 u, v;
    cin >> u >> v;
    G[u].insert(v);
    G[v].insert(u);
  }

  for(int i = 0; i < Q;i++) {
    i64 q, a, b;
    cin >> q >> a >> b;
    if(q == 0) {
      i64 c;
      cin >> c;
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
