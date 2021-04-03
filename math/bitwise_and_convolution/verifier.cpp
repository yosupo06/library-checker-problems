#include "params.h"
#include "testlib.h"

int main() {
  registerValidation();

  const int n = 1 << inf.readInt(0, N_MAX);
  inf.readChar('\n');
  for (int t = 0; t != 2; ++t) {
    for (int i = 0; i != n; i += 1) {
      inf.readInt(0, MOD - 1);
      if (i + 1 != n) {
        inf.readSpace();
      } else {
        inf.readChar('\n');
      }
    }
  }
  inf.readEof();
  
  return 0;
}
