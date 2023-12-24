#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  long long n = inf.readInt(0, NM_MAX);
  inf.readSpace();
  long long m = inf.readInt(0, NM_MAX);
  inf.readChar('\n');
  ensure(n * m <= NM_MAX);

  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      inf.readInt(0, MOD - 1);
      if (j + 1 != m) inf.readSpace();
    }
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
