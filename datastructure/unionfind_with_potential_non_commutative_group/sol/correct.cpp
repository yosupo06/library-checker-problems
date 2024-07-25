#include <array>
#include <cstdio>
#include <vector>
#include "acl.h"

using namespace std;
using namespace atcoder;

template<class G, G(*id)(), G(*op)(const G&, const G&), G(*inv)(const G&)>
struct DSU {
  vector<int> bos, sz;
  vector<G> _pot;
  int size;

  DSU(int _size) : bos(_size), sz(_size, 1), _pot(_size, id()), size(_size) {
    iota(bos.begin(), bos.end(), 0);
  }

  int query(int v) {
    if (bos[v] == v) {
      return v;
    } else {
      int tmp = query(bos[v]);
      _pot[v] = op(_pot[bos[v]], _pot[v]);
      return bos[v] = tmp;
    }
  }

  //op(v1, d) = v2
  bool merge(int v1, int v2, G d) {
    int b1 = query(v1), b2 = query(v2);

    if (b1 == b2)
      return op(inv(_pot[v1]), _pot[v2]) == d;

    if (sz[b1] > sz[b2]) {
      swap(b1, b2), swap(v1, v2);
      d = inv(d);
    }
    bos[b1] = b2, sz[b2] += sz[b1], _pot[b1] = op(op(_pot[v2], inv(d)), inv(_pot[v1]));

    return true;
  }

  //op(inv(v1), v2)
  G query(int v1, int v2) {
    query(v1), query(v2);
    return op(inv(_pot[v1]), _pot[v2]);
  }
};

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

  DSU<matrix, id, op, inv> dsu(N);
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
      printf("%d\n", dsu.merge(v, u, x));
    } else {
      if (dsu.query(u) != dsu.query(v)) {
        printf("%d\n", -1);
      } else {
        matrix M = dsu.query(v, u);
        printf("%d %d %d %d\n", M[0][0].val(), M[0][1].val(), M[1][0].val(), M[1][1].val());
      }
    }
  }

  return 0;
}
