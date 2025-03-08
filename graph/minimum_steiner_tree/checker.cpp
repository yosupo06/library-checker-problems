#include <numeric>
#include <utility>
#include <vector>
#include "testlib.h"

using namespace std;

struct E {
  int U, V, W;
};

struct DSU {
  vector<int> bos, sz;
  int size;

  DSU(int _size) : bos(_size), sz(_size, 1), size(_size) {
    iota(bos.begin(), bos.end(), 0);
  }

  int query(int v) {
    if (bos[v] == v)
      return v;
    else
      return bos[v] = query(bos[v]);
  }

  bool merge(int v1, int v2) {
    int b1 = query(v1), b2 = query(v2);

    if (b1 == b2)
      return false;

    if (sz[b1] > sz[b2])
      swap(b1, b2);
    bos[b1] = b2, sz[b2] += sz[b1];

    return true;
  }
};

long long read_ans(int N, int M, vector<E> E, int K, vector<int> X, InStream &stream) {
  long long Y = stream.readLong();
  int Z = stream.readInt(K - 1, N - 1);
  long long sum = 0;
  DSU dsu(N);
  for(int i = 0; i < Z; i++) {
    int eid = stream.readInt(0, M - 1);
    auto e = E[eid];
    if (dsu.query(e.U) == dsu.query(e.V))
      stream.quit(_wa, "input isn't tree.");
    dsu.merge(e.U, e.V);
    sum += e.W;
  }

  if (Y != sum)
    stream.quitf(_wa, "Y(" I64 ") isn't correct, sum = " I64, Y, sum);

  int group = dsu.query(X[0]);
  for(int x : X)
    if (group != dsu.query(x))
      stream.quitf(_wa, "X doesn't form a component.");

  return Y;
}

int main(int argc, char *argv[]) {
  registerTestlibCmd(argc, argv);

  int N = inf.readInt();
  int M = inf.readInt();
  vector<E> E(M);
  for(auto &[Ui, Vi, Wi] : E) {
    Ui = inf.readInt();
    Vi = inf.readInt();
    Wi = inf.readInt();
  }
  int K = inf.readInt();
  vector<int> X(K);
  for(int &x : X)
    x = inf.readInt();

  long long Y_ans = read_ans(N, M, E, K, X, ans);
  long long Y_ouf = read_ans(N, M, E, K, X, ouf);

  if (Y_ans < Y_ouf)
    quitf(_wa, "There exist better solution.");
  if (Y_ans > Y_ouf)
    quitf(_fail, "Participant find better answer.");

  quitf(_ok, "OK: " I64, Y_ouf);
}
