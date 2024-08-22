#include <iostream>
#include <cassert>

#include "testlib.h"
#include "params.h"

using namespace std;

struct UnionFind {
  int n;
  vector<int> p, r;
  UnionFind(int _n = 0) : n(_n), p(n, -1), r(n, 1) {}
  void merge(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    int x = group(a), y = group(b);
    if (x == y) return; // same
    if (r[x] < r[y]) swap(x, y);
    p[y] = x;
    r[x] += r[y];
  }
  int group(int a) {
    assert(0 <= a && a < n);
    if (p[a] == -1) return a;
    return p[a] = group(p[a]);
  }
  bool same(int a, int b) {
    assert(0 <= a && a < n);
    assert(0 <= b && b < n);
    return group(a) == group(b);
  }
};

int main() {
  registerValidation();

  int n = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  int Q = inf.readInt(Q_MIN, Q_MAX);
  inf.readChar('\n');

  UnionFind uf(n);
  for (int i = 0; i < n - 1; i++) {
    int a = inf.readInt(0, n - 1);
    inf.readSpace();
    int b = inf.readInt(0, n - 1);
    inf.readChar('\n');

    ensure(!uf.same(a, b));
    uf.merge(a, b);
  }

  for (int q = 0; q < Q; ++q) {
    inf.readInt(0, n - 1, "s");
    inf.readSpace();
    inf.readInt(0, n - 1, "t");
    inf.readSpace();
    inf.readInt(0, n - 1, "i");
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
