#include "params.h"
#include "testlib.h"
#include <vector>

int main() {
  registerValidation();

  int n = inf.readInt(N_MIN, N_MAX);
  inf.readChar('\n');
  ensure(n % 2 == 0);

  std::vector<std::vector<int>> a(n, std::vector<int>(n));

  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != n; ++j) {
      a[i][j] = inf.readInt(0, MOD - 1);
      if (j + 1 != n) {
        inf.readSpace();
      }
    }
    inf.readChar('\n');
  }
  inf.readEof();

  for (int i = 0; i != n; ++i) {
    ensure(a[i][i] == 0);
  }

  for (int i = 0; i != n; ++i) {
    for (int j = 0; j != i; ++j) {
      ensure(a[i][j] == a[j][i]);
    }
  }
}
