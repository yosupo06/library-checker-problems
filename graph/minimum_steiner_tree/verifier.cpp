#include "testlib.h"
#include "params.h"
#include <numeric>
#include <vector>

using namespace std;

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

int main() {
  registerValidation();

  int N = inf.readInt(1, N_MAX);
  inf.readSpace();
  int M = inf.readInt(N - 1, M_MAX);
  inf.readChar('\n');

  DSU dsu(N);
  int cc = N;
  for(int i = 0; i < M; i++) {
    int Ui = inf.readInt(0, N - 1);
    inf.readSpace();
    int Vi = inf.readInt(0, N - 1);
    inf.readSpace();
    inf.readInt(W_MIN, W_MAX);
    inf.readChar('\n');

    if (dsu.merge(Ui, Vi)) cc -= 1;
  }

  ensuref(cc == 1, "The given graph is not connected.");

  int K = inf.readInt(1, min(N, (int)K_MAX));
  inf.readChar('\n');
  vector<int> X(K);
  for(int i = 0; i < K; i++) {
    X[i] = inf.readInt(0, N - 1);
    if (i + 1 < K) inf.readSpace();
    else inf.readChar('\n');
  }

  for(int i = 1; i < K; i++)
    ensuref(X[i - 1] < X[i], "The given X is not strictly increasing.");

  inf.readEof();

  return 0;
}
