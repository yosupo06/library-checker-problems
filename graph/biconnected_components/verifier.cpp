#include "testlib.h"
#include "params.h"
#include <utility>
#include <set>

int main() {
  registerValidation();

  int n = inf.readInt(N_MIN, N_MAX);
  inf.readSpace();
  int m = inf.readInt(M_MIN, M_MAX);
  inf.readEoln();

  std::set<std::pair<int, int>> es;
  for (int i = 0; i != m; i += 1) {
    int a = inf.readInt(0, n - 1);
    inf.readSpace();
    int b = inf.readInt(0, n - 1);
    inf.readEoln();
    ensure(a != b);
    auto e = std::minmax({a, b});
    ensure(!es.count(e));
    es.emplace(e);
  }

  inf.readEof();
}
