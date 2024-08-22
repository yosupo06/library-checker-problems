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
      char c = inf.readChar();
      ensure(c == '0' || c == '1');
    }
    inf.readChar('\n');
  }
  inf.readEof();
  return 0;
}
