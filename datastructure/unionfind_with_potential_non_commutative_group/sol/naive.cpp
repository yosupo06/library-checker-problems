#include <array>
#include <cstdio>
#include <vector>
#include "acl.h"

using namespace std;
using namespace atcoder;

using mint = modint998244353;
using matrix = array<array<mint, 2>, 2>;

matrix id() {
  matrix M;
  M[0][0] = M[1][1] = 1, M[0][1] = M[1][0] = 0;
  return M;
}

matrix op(const matrix &A, const matrix &B) {
  matrix C;
  for(int i : {0, 1})
    for(int k : {0, 1})
      for(int j : {0, 1})
        C[i][j] += A[i][k] * B[k][j];
  return C;
}

matrix inv(const matrix &A) {
  matrix M = A;
  swap(M[0][0], M[1][1]);
  M[0][1] *= -1, M[1][0] *= -1;
  return M;
}

int main() {
  int N, Q;
  scanf("%d %d", &N, &Q);

  vector<vector<pair<int, matrix>>> g(N);
  vector<matrix> M(N, id());
  vector<int> vis(N);
  iota(vis.begin(), vis.end(), 0);

  //op(M[v1], d) = M[v2]
  auto try_add = [&](int v1, int v2, matrix d) {
    g[v1].emplace_back(v2, d);
    g[v2].emplace_back(v1, inv(d));

    bool valid = true;
    vector MP(N, id());
    vector visp(N, -1);
    int s = 0;
    auto dfs = [&](int v, auto &&self) -> void {
      visp[v] = s;
      for(auto [u, x] : g[v]) {
        if (visp[u] != -1) {
          valid = valid and op(MP[v], x) == MP[u];
        } else {
          MP[u] = op(MP[v], x);
          self(u, self);
        }
      }
    };
    for(int v = 0; v < N; v++) if (visp[v] == -1) {
      dfs(v, dfs);
      s++;
    }

    if (valid) {
      M.swap(MP);
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
      matrix x;
      for(int i : {0, 1}) for(int j : {0, 1}) {
        int c; 
        scanf("%d", &c);
        x[i][j] = c;
      }
      printf("%d\n", try_add(v, u, x));
    } else {
      if (vis[u] != vis[v]) {
        printf("%d\n", -1);
      } else {
        matrix R = op(inv(M[v]), M[u]);
        printf("%d %d %d %d\n", R[0][0].val(), R[0][1].val(), R[1][0].val(), R[1][1].val());
      }
    }
  }

  return 0;
}
