#include "testlib.h"
#include "params.h"

int main() {
  registerValidation();
  const int N = inf.readInt(N_MIN, N_MAX);
  inf.readChar('\n');
  for (int i = 0; i < N; ++i) {
    if (i > 0) {
      inf.readChar(' ');
    }
    inf.readInt(0, MOD - 1);
  }
  inf.readChar('\n');
  inf.readEof();
  return 0;
}
