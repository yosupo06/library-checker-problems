#include "params.h"
#include "testlib.h"
#include <algorithm>
#include <set>
#include <utility>

int main() {
  registerValidation();

  int n = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  int m = inf.readInt(M_MIN, M_MAX);
  inf.readChar('\n');
  for (int i = 0; i < n; ++i) {
    inf.readInt(0, MOD - 1);
    if (i != n - 1) {
      inf.readSpace();
    } else {
      inf.readChar('\n');
    }
  }

  std::set<std::pair<int, int>> edges;
  for (int i = 0; i < m; ++i) {
    int u = inf.readInt(0, n - 1);
    inf.readSpace();
    int v = inf.readInt(0, n - 1);
    ensure(u != v);
    ensure(edges.insert(std::minmax(u, v)).second);
    inf.readChar('\n');
  }

  inf.readEof();
}
