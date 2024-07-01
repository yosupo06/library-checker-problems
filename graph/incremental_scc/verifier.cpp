#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();

  int n = inf.readInt(MIN_N, MAX_N);
  inf.readSpace();
  int m = inf.readInt(MIN_M, MAX_M);
  inf.readChar('\n');

  for (int i = 0; i < n; ++i) {
    if (i) inf.readSpace();
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');

  for (int i = 0; i < m; i++) {
    inf.readInt(0, n - 1);
    inf.readSpace();
    inf.readInt(0, n - 1);
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
